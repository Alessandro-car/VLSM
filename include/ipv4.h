#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/utils.h"

#define NUM_OCTETS     4
#define OCTET_BIT_SIZE 8
#define OCTET_DEC_SIZE 3
#define N_DOTS 				 3
#define DIM_DEC_IP 		 ((NUM_OCTETS * OCTET_DEC_SIZE) + N_DOTS)
#define DIM_BIN_IP     ((NUM_OCTETS * OCTET_BIT_SIZE) + N_DOTS)

typedef struct {
	char* address;
	size_t cidr;
	char* sub_mask;
} ipv4_t;

char* get_addr(ipv4_t ip_addr);
void set_addr(ipv4_t* ip_addr, const char* addr);
size_t get_cidr(ipv4_t ip_addr);
void set_cidr(ipv4_t* ip_addr, size_t cidr);
char* get_sub_mask(ipv4_t ip_addr);
void set_sub_mask(ipv4_t* ip_addr, const char* sub_mask);
void compute_sub_mask(ipv4_t* ip_addr);
