#include "../include/subnet.h"

address_t get_net_addr(subnet_t subnet) {
	return subnet.net_addr;
}

void set_net_addr(subnet_t* subnet, const address_t net_addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		strcpy(subnet->net_addr.addr[i], net_addr.addr[i]);
	}
}

address_t* get_host_range(subnet_t subnet) {
	return subnet.host_range;
}

void set_host_range(subnet_t* subnet, const address_t* host_range) {
	subnet->host_range = calloc(subnet->num_subnet, sizeof(address_t));
	for (size_t i = 0; i < subnet->num_subnet; i++) {
		for (int j = 0; j < NUM_OCTETS; j++) {
			strcpy(subnet->host_range[i].addr[j], host_range[i].addr[j]);
		}
	}
}

address_t get_broadcast_addr(subnet_t subnet) {
	return subnet.broadcast_addr;
}

void set_broadcast_addr(subnet_t* subnet, const address_t broad_addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		strcpy(subnet->broadcast_addr.addr[i], broad_addr.addr[i]);
	}
}
