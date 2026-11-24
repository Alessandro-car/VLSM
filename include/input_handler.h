#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "address_utils.h"

#define MAX_SUBNETS 65535

bool ip_address_input(address_t* addr);
bool cidr_input(size_t* cidr);
bool num_subnet_input(size_t* num_subnet);
int* num_host_subnet_input(size_t num_subnet);

#endif
