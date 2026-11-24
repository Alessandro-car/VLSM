#include "../include/address_utils.h"

address_t get_next_address(const address_t addr) {
	address_t next_addr = addr;
	for (size_t idx = NUM_OCTETS; idx > 0; idx--) {
		size_t i = idx - 1;
		if (next_addr.addr[i] < 255) {
			next_addr.addr[i] += 1;
			return next_addr;
		}
		next_addr.addr[i] = 0;
	}

	address_t overflow = { 0 };
	return overflow;
}


size_t compute_n_host_bit(int num_host) {
	return (size_t) ceil(log2((double) num_host + 2));
}


void print_address(address_t addr) {
	for (size_t i = 0; i < NUM_OCTETS; i++) {
		printf("%d", addr.addr[i]);
		if (i < NUM_OCTETS - 1) printf(".");
	}
}
