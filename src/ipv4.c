#include "../include/ipv4.h"

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

void compute_sub_mask(ipv4_t* ip_addr) {
	char* sub_mask = calloc(DIM_DEC_IP + 1, sizeof(char));
	for (size_t i = 0; i < ip_addr->cidr / OCTET_BIT_SIZE; i++) {
		strcat(sub_mask, "255.");
	}
	int num = 0;
	for (size_t i = 0; i < ip_addr->cidr % OCTET_BIT_SIZE; i++) {
		num += pow(2, (OCTET_BIT_SIZE - 1 - i));
	}
	char* str_num = calloc(OCTET_DEC_SIZE + 1, sizeof(char));
	itoa(num, str_num);
	strcat(sub_mask, str_num);
}
