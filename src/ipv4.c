#include "../include/ipv4.h"
#include <string.h>

address_t get_addr(ipv4_t ip_addr) {
	return ip_addr.addr;
}

void set_addr(ipv4_t* ip_addr, const address_t addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		strcpy(ip_addr->addr.addr[i], addr.addr[i]);
	}
}

size_t get_cidr(ipv4_t ip_addr) {
	return ip_addr.cidr;
}

void set_cidr(ipv4_t* ip_addr, size_t cidr) {
	ip_addr->cidr = cidr;
}

address_t get_sub_mask(ipv4_t ip_addr) {
	return ip_addr.sub_mask;
}

void set_sub_mask(ipv4_t* ip_addr, const address_t sub_mask) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		strcpy(ip_addr->sub_mask.addr[i], sub_mask.addr[i]);
	}
}

void compute_sub_mask(ipv4_t* ip_addr) {
	int n_octet = ip_addr->cidr / OCTET_BIT_SIZE;
	int rem_bits = ip_addr->cidr % OCTET_BIT_SIZE;
	int i = 0;
	for (; i < n_octet && i < NUM_OCTETS; i++) {
		for (int j = 0; j < OCTET_BIT_SIZE; j++)
			ip_addr->sub_mask.addr[i][j] = '1';
		ip_addr->sub_mask.addr[i][OCTET_BIT_SIZE] = '\0';
	}
	if (rem_bits > 0 && i < NUM_OCTETS) {
		for (int j = 0; j < rem_bits; j++) {
			ip_addr->sub_mask.addr[i][j] = '1';
		}
		for (int j = rem_bits; j < OCTET_BIT_SIZE; j++) {
			ip_addr->sub_mask.addr[i][j] = '0';
		}
		ip_addr->sub_mask.addr[i][OCTET_BIT_SIZE] = '\0';
		i++;
	}

	for (; i < NUM_OCTETS; i++) {
		for (int j = 0; j < OCTET_BIT_SIZE; j++) {
			ip_addr->sub_mask.addr[i][j] = '0';
		}
		ip_addr->sub_mask.addr[i][OCTET_BIT_SIZE] = '\0';
	}
}

void print_ipv4_scheme(const ipv4_t ip_addr) {
	address_t dec_addr;
	address_t dec_sub_mask;
	binary_to_dec_addr(&dec_addr, ip_addr.addr);
	binary_to_dec_addr(&dec_sub_mask, ip_addr.sub_mask);
	printf("IP address: ");
	for (int i = 0; i < NUM_OCTETS; i++) {
		printf("%s", dec_addr.addr[i]);
		if (i < NUM_OCTETS - 1)
			printf(".");
	}
	printf("/%zu", ip_addr.cidr);
	printf("\nSubnet mask: ");
	for (int i = 0; i < NUM_OCTETS; i++) {
		printf("%s", dec_sub_mask.addr[i]);
		if (i < NUM_OCTETS - 1) {
			printf(".");
		}
	}
}
