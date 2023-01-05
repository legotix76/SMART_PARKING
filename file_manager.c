#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_manager.h"

const char * file_name = "Availability.txt";

int read_file_to_line_buffer(char line_buffer[100][20]){
  // Open the file as read-only.
  FILE *file = fopen(file_name, "r"); 
  
  char line[20]; // Line buffer, for each line in the file

  int i = 0;
  // While there are still lines to be read, and we haven't gone over 100 lines.
  while( fgets( line, 20, file) != NULL && i<100)
  {
    // For each line read from the file, copy it to the line buffer
    strcpy(line_buffer[i], line);
    i++;
  }

  fclose(file); // Close the file when done
  return i; // Return the number of lines read
}

// Extracts and returns the state of a line
int get_state_from_line(char line[20]){
  char *p = line; // Copy the pointer for the beginning of the line
  while(*p++ != ':'); // Move the pointer along until we get to ':'
  return *p == '1'; // Check if the character pointed at is '1'
}

// Extracts the states of the slots from an array of character strings
void get_states_from_lines(char line_buffer[100][20], int states[100], int len){

  // Foreach line in the line buffer
  for(int i=0; i<len; i++){
    char *line = line_buffer[i];
    // Obtain the state from the line and store it in the supplied array
    states[i] = get_state_from_line(line);
  }
}

// Write the slot states to file.
void write_states_to_file(int states[100], int len){

  // Open the file as write-only. We will override the entire file.
  FILE *file = fopen(file_name, "w");

  // For each slot, write the slot number and its availability to file.
  for(int i=0; i<len; i++){
    fprintf(file, "%d:%d\n", i+1, states[i]);
  }
  
  fclose(file);
}