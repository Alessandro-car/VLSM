#ifndef SUBNET_H_
#define SUBNET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "address_utils.h"
#include "ipv4.h"

typedef struct {
	ipv4_t		 net_addr;
	size_t 		 num_host;
	address_t* host_range;
	address_t  broad_addr;
} subnet_t;

ipv4_t get_net_addr(subnet_t subnet);
void set_net_addr(subnet_t* subnet, const ipv4_t net_addr);
size_t get_num_host(subnet_t subnet);
void set_num_host(subnet_t* subnet, size_t num_host);
address_t* get_host_range(subnet_t subnet);
void set_host_range(subnet_t* subnet);
address_t get_broadcast_addr(subnet_t subnet);
void set_broadcast_addr(subnet_t* subnet);

size_t compute_n_host_bit(subnet_t subnet);
void change_cidr(subnet_t* subnet, size_t n_host_bit);
void print_scheme(subnet_t subnet);
#endif
