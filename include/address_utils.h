#ifndef ADDRESS_UTILS_H_
#define ADDRESS_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "utils.h"

#define NUM_OCTETS      4
#define OCTET_BIT_SIZE  8
#define TOTAL_SIZE_IPV4 (NUM_OCTETS * OCTET_BIT_SIZE)

typedef struct {
	int addr[NUM_OCTETS];
} address_t;

address_t get_next_address(const address_t addr);
size_t compute_n_host_bit(int num_host);
void print_address(address_t addr);

#endif

