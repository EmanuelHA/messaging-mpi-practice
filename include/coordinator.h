#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "protocol.h"

#define COORDINATOR 0

int process_request();

int route_message(Message *msg);

void update_log();

int save_log_to_disk();

#endif
