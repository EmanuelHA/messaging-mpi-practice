#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "protocol.h"

int process_request();

int route_message();

void update_log();

int save_log_to_disk();

#endif
