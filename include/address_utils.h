#ifndef ADDRESS_UTILS_H_
#define ADDRESS_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"

#define NUM_OCTETS     4
#define OCTET_BIT_SIZE 8
#define OCTET_DEC_SIZE 3
#define N_DOTS 				 3
#define DIM_DEC_IP 		 ((NUM_OCTETS * OCTET_DEC_SIZE) + N_DOTS)
#define DIM_BIN_IP     ((NUM_OCTETS * OCTET_BIT_SIZE) + N_DOTS)

#include "utils.h"

typedef struct {
	char addr[NUM_OCTETS][OCTET_BIT_SIZE + 1];
} address_t;


void binary_to_dec_addr(address_t* dec_addr, const address_t bin_addr);
void octet_to_decimal_str(const char octet[OCTET_BIT_SIZE + 1], char* out, size_t out_size);

#endif

