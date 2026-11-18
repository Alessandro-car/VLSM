#include "include/ipv4.h"

char* get_addr(ipv4_t ip_addr) {
	return ip_addr.address;
}

void set_addr(ipv4_t* ip_addr, const char* addr) {
	ip_addr->address = calloc(strlen(addr) + 1, sizeof(char));
	strcpy(ip_addr->address, addr);
}

size_t get_cidr(ipv4_t ip_addr) {
	return ip_addr.cidr;
}

void set_cidr(ipv4_t* ip_addr, size_t cidr) {
	ip_addr->cidr = cidr;
}

char* get_sub_mask(ipv4_t ip_addr) {
	return ip_addr.sub_mask;
}

void set_sub_mask(ipv4_t* ip_addr, const char* sub_mask) {
	ip_addr->sub_mask = calloc(strlen(sub_mask) + 1, sizeof(char));
	strcpy(ip_addr->sub_mask, sub_mask);
}
