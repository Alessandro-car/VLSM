#ifndef SUBNET_H_
#define SUBNET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "address_utils.h"
#include "ipv4.h"

typedef struct {
	ipv4_t		 net_addr;
	size_t 		 num_addr;
	address_t* host_range;
	address_t  broad_addr;
} subnet_t;

ipv4_t get_net_addr(subnet_t subnet);
void set_net_addr(subnet_t* subnet, const ipv4_t net_addr);
size_t get_num_addr(subnet_t subnet);
void set_num_addr(subnet_t* subnet, size_t num_addr);
address_t* get_host_range(subnet_t subnet);
void set_host_range(subnet_t* subnet);
address_t get_broadcast_addr(subnet_t subnet);
void set_broadcast_addr(subnet_t* subnet);

void change_cidr(subnet_t* subnet, size_t n_host_bit);
bool subnet_create(subnet_t* subnet, address_t start, size_t n_host_bit);
void subnet_destroy(subnet_t* subnet);
void print_scheme(subnet_t subnet);
#endif
