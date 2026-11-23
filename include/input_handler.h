#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "address_utils.h"

void ip_address_input(address_t* addr);
size_t cidr_input();
size_t num_subnet_input();
int* num_host_subnet_input(size_t num_subnet);

#endif
