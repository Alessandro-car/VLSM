#ifndef SUBNET_H_
#define SUBNET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "address_utils.h"

typedef struct {
	address_t	 net_addr;
	size_t 		 num_subnet;
	address_t* host_range;
	address_t  broadcast_addr;
} subnet_t;

address_t get_net_addr(subnet_t subnet);
void set_net_addr(subnet_t* subnet, const address_t net_addr);
address_t* get_host_range(subnet_t subnet);
void set_host_range(subnet_t* subnet, const address_t* host_range);
address_t get_broadcast_addr(subnet_t subnet);
void set_broadcast_addr(subnet_t* subnet, const address_t broad_addr);

#endif
