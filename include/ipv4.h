#ifndef IPV4_H_
#define IPV4_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "address_utils.h"

typedef struct {
	char 	 address[NUM_OCTETS][OCTET_BIT_SIZE];
	size_t cidr;
	char   sub_mask[NUM_OCTETS][OCTET_BIT_SIZE];
} ipv4_t;

char* get_addr(ipv4_t ip_addr);
void set_addr(ipv4_t* ip_addr, const char addr[NUM_OCTETS][OCTET_BIT_SIZE]);
size_t get_cidr(ipv4_t ip_addr);
void set_cidr(ipv4_t* ip_addr, size_t cidr);
char* get_sub_mask(ipv4_t ip_addr);
void set_sub_mask(ipv4_t* ip_addr, const char sub_mask[NUM_OCTETS][OCTET_BIT_SIZE]);
void compute_sub_mask(ipv4_t* ip_addr);

#endif
