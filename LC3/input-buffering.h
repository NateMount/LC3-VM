#ifndef _LC3_INPUT_BUFF
#define _LC3_INPUT_BUFF

void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);

#endif