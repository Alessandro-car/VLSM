#ifndef IPV4_H_
#define IPV4_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "address_utils.h"

typedef struct {
	address_t addr;
	size_t 		cidr;
	address_t sub_mask;
} ipv4_t;

address_t get_addr(ipv4_t ip_addr);
void set_addr(ipv4_t* ip_addr, const address_t addr);
size_t get_cidr(ipv4_t ip_addr);
void set_cidr(ipv4_t* ip_addr, size_t cidr);
address_t get_sub_mask(ipv4_t ip_addr);
void set_sub_mask(ipv4_t* ip_addr, const address_t sub_mask);
void compute_sub_mask(ipv4_t* ip_addr);
void compute_net_addr(ipv4_t* ip_addr);
void print_ipv4_scheme(const ipv4_t ip_addr);

#endif
