#ifndef CLIENT_H
#define CLIENT_H

#include "protocol.h"

int connect();
int dissconect();

int send_message(char* msg);
int receive_message(char* msg);

void* launch_gui_thread(void* args);
void show_message(const char* msg);
void get_user_input(char* msg);

#endif
