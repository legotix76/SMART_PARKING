#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

int read_file_to_line_buffer(char [100][20]);
int get_state_from_line(char line[20]);
void get_states_from_lines(char line_buffer[100][20], int states[100], int len);

void write_states_to_file(int[100], int);

#endif