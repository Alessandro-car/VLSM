#include "../include/ipv4.h"
#include <string.h>

address_t get_addr(ipv4_t ip_addr) {
	return ip_addr.addr;
}

void set_addr(ipv4_t* ip_addr, const address_t addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		ip_addr->addr.addr[i] = addr.addr[i];
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
		ip_addr->sub_mask.addr[i] = sub_mask.addr[i];
	}
}

void compute_sub_mask(ipv4_t* ip_addr) {
	size_t n_octet = ip_addr->cidr / OCTET_BIT_SIZE;
	size_t rem_bits = ip_addr->cidr % OCTET_BIT_SIZE;

	for (size_t i = 0; i < NUM_OCTETS; i++) {
		if (i < n_octet)
			ip_addr->sub_mask.addr[i] = 0xFF;
		else if (i == n_octet && rem_bits > 0)
			ip_addr->sub_mask.addr[i] = (0xFFu << (OCTET_BIT_SIZE - rem_bits)) & 0xFFu;
		else
			ip_addr->sub_mask.addr[i] = 0;
	}
}

void compute_net_addr(ipv4_t* ip_addr) {
	compute_sub_mask(ip_addr);
	for (int i = 0; i < NUM_OCTETS; i++)
		ip_addr->addr.addr[i] &= ip_addr->sub_mask.addr[i];
}

