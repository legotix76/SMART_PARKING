// Contains two simple functions used for the commande line interface.

#include "interface.h"
#include "welcome.h"
#include <stdio.h>
#include <stdlib.h>

char cmd_line_input_buffer[64];

// Read a line from the console and return an int.
// More reliable than scnaf as this while clear the entire line every
int read_int_from_cmd(){
  fgets(cmd_line_input_buffer, 64, stdin);
  return strtol(cmd_line_input_buffer, NULL, 10);
}

// Display the smart parking logo.
// The logo is stored seperatly in "welcome.h" to avoid accidently disturbing the alignement.
void print_welcome_msg(){
  printf("%s", welcome_msg);
}