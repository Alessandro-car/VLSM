#ifndef SUBNET_H_
#define SUBNET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "address_const.h"

typedef struct {
	char   net_addr[NUM_OCTETS][OCTET_BIT_SIZE];
	size_t num_subnet;
	char** host_range;
	char  broadcast_addr[NUM_OCTETS][OCTET_BIT_SIZE];
} subnet_t;

char* get_net_addr(subnet_t subnet);
void set_net_addr(subnet_t* subnet, const char net_addr[OCTET_BIT_SIZE][OCTET_BIT_SIZE]);
char** get_host_range(subnet_t subnet);
void set_host_range(subnet_t* subnet, const char** host_range);
char* get_broadcast_addr(subnet_t subnet);
void set_broadcast_addr(subnet_t* subnet, const char broadcast_addr[NUM_OCTETS][OCTET_BIT_SIZE]);

#endif
