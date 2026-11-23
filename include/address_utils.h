#ifndef ADDRESS_UTILS_H_
#define ADDRESS_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"

#define NUM_OCTETS      4
#define OCTET_BIT_SIZE  8
#define TOTAL_SIZE_IPV4 (NUM_OCTETS * OCTET_BIT_SIZE)
#define OCTET_DEC_SIZE  3
#define N_DOTS 				  3
#define DIM_DEC_IP 		  ((NUM_OCTETS * OCTET_DEC_SIZE) + N_DOTS)
#define DIM_BIN_IP      ((NUM_OCTETS * OCTET_BIT_SIZE) + N_DOTS)

#include "utils.h"

typedef struct {
	int addr[NUM_OCTETS];
} address_t;


address_t get_next_address(const address_t addr);
void print_address(address_t addr);

#endif

