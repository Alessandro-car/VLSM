#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
