#include <stdio.h>
#include <stdlib.h>
#include "file_manager.h"
#include "interface.h"

char lines[100][20];
int states[100];


// Function prototypes for the different menus.
void menu_availability();
void menu_all_available();
void menu_available_num();
void menu_reservation();
void menu_free();


// Main menu.
int main(void) {
  int choice; 
  

  // Loop forever. 
  // To end the program the user must enter '6'. This while cause
  // the 'main' to return, ending the program. 
  while(1){

    // Clear the screen and display the logo
    system("clear");
    print_welcome_msg();

    //Display the menu
    printf("MAIN MENU:\n");
    printf("1 - Check the availability of a specific car slot\n");
    printf("2 - Display all available car slots\n");
    printf("3 - Display the number of available car slots\n");
    printf("4 - Make a reservation\n"); 
    printf("5 - Free a slot\n");
    printf("6 - Exit\n");
    printf("Selection: ");
    
    // Variable to loop until a correct choice has been made.
    int correct_choice = 0;

    // Check if the input is correct and start the selected function
    while(!correct_choice){
      correct_choice = 1; // Initialy set to 1. Will get set to 0 if an incorrect is made. 
      choice = read_int_from_cmd();

      // Execute the chosen function
      switch(choice) {
        case 1: 
          menu_availability();
          break;
        ;
        case 2: 
          menu_all_available();
          break;
        ;
        case 3: 
          menu_available_num();
          break;
        ;
        case 4: 
          menu_reservation();
          break;
        ;
        case 5:
          menu_free();
          break;
        case 6:
          // Return from main(), ending the program
          return 1;
        ;
        // If the user input is wrong
        default:
          printf("ERROR. Please enter a correct number: ");
          correct_choice = 0;
          break;

      }
    }
  }
}

// Display the number of available slots
void menu_availability(){
  
  system("clear");
  print_welcome_msg();

  while(1){
    printf("SLOT AVAILABILITY: \n");
    // Read the file to the lines buffer and get the number of lines
    int len = read_file_to_line_buffer(lines);
    printf("There is a total of %d parking slots.\n" ,len);

    int choice;
    printf("Input a slot number, or (-1) to exit: ");
    choice = read_int_from_cmd();
    if(choice ==-1) return;
    
    while(choice > len || choice <1){
      printf("Please enter a valid slot number: ");
      choice = read_int_from_cmd();
      if(choice ==-1) return;
    }

    // Parse the requested line.
    int state = get_state_from_line(lines[choice-1]);
    if (state){
      printf("Slot %d is unavaible.\n", choice);
    }
    else{
      printf("Slot %d is available.\n", choice);
    }
  }
}

// Display all availables slots
void menu_all_available(){
  system("clear");
  print_welcome_msg();
  printf("AVAILABLE SLOTS ('--' is unavaible): \n");

  //Read the file and get the state
  int len = read_file_to_line_buffer(lines);
  get_states_from_lines(lines, states, len);
  
  // Check and diplay the available slot in the form of a grid
  for(int i=0; i<len; i++){
    if(!states[i]){
      printf("%4d", i+1);
    }
    else{
      printf("  --");
    }
    
    // Every ten slots, go to a new line
    if((i+1)%10==0) printf("\n");
  }

  printf("Press Any Key to Continue\n");  
  getchar(); 
}


// Check and count all available slots
void menu_available_num(){
  system("clear");
  print_welcome_msg();

  printf("NUMBER OF AVAILABLE SLOTS: \n");
  
  int len = read_file_to_line_buffer(lines);
  get_states_from_lines(lines, states, len);
  
  // Init the counter
  int counter = 0;
 
  // Increment the counter if the slot is free
  for(int i=0; i<len; i++){ 
    if(states[i]==0){
        counter = counter + 1; 
      }
  }
  // Display the number of available slot
  printf("There are %d slots available.\n",counter);

  printf("Press Any Key to Continue\n");

  // Wait for user input before returning to main menu
  getchar(); 
  
}

// Change the state of a slot to "RESERVED"
void menu_reservation(){
  system("clear");
  print_welcome_msg();

  printf("SLOT RESERVATION: \n");

  int len = read_file_to_line_buffer(lines);
  get_states_from_lines(lines, states, len);

  // The variable is egal to 0 while the operation is not ended
  int slot_reserved = 0;

  // Ask the user a correct choice while his input is not correct
  while(!slot_reserved){
    printf("Enter a slot you wish to reserve: ");
    int choice = read_int_from_cmd();

    while(choice < 1 || choice > len){
      printf("Please enter a valid slot number: ");
      choice = read_int_from_cmd();
    }

    // Case if the slot is free
    if(states[choice-1]){
      printf("Sorry, that slot is already taken. \n");
    }
    
    //Case if the slot is reserved
    else{
      slot_reserved = 1;
      states[choice-1] = 1;
      printf("Slot number %d has been reserved. \n", choice);

      write_states_to_file(states, len);
    }
  }
  printf("Press Any Key to Continue\n");  
  getchar(); 
}

// Change the state of a slot to "FREE" 
//(similar to the menu_reservation function)
void menu_free(){
  system("clear");
  print_welcome_msg();

  printf("SLOT FREEING: \n");
  
  int len = read_file_to_line_buffer(lines);
  get_states_from_lines(lines, states, len);

  
  int slot_change = 0;

  while(!slot_change){
    printf("Enter a slot you wish to free: ");
    int choice;
    choice = read_int_from_cmd();

    
    while(choice < 1 || choice > len){
      printf("Please enter a valid slot number: ");
      choice = read_int_from_cmd();
    }

    if(!states[choice-1]){
      printf("Sorry, that slot is already free. \n");
    }
    else{
      slot_change = 1;
      states[choice-1] = 0;
      printf("Slot number %d has been freed. \n", choice);
      write_states_to_file(states, len);
    }
  }
  
  printf("Press Any Key to Continue\n");  
  getchar(); 
}