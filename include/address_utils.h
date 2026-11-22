#ifndef ADDRESS_UTILS_H_
#define ADDRESS_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define NUM_OCTETS     4
#define OCTET_BIT_SIZE 8
#define OCTET_DEC_SIZE 3
#define N_DOTS 				 3
#define DIM_DEC_IP 		 ((NUM_OCTETS * OCTET_DEC_SIZE) + N_DOTS)
#define DIM_BIN_IP     ((NUM_OCTETS * OCTET_BIT_SIZE) + N_DOTS)

#include "utils.h"

void binary_to_dec_addr(char dec_addr[NUM_OCTETS][OCTET_DEC_SIZE], const char bin_addr[NUM_OCTETS][OCTET_BIT_SIZE]);
void pretty_print_addr(char* converted_addr, const char addr[NUM_OCTETS][OCTET_DEC_SIZE]);

#endif

