#include "../include/subnet.h"

address_t get_net_addr(subnet_t subnet) {
	return subnet.net_addr;
}

void set_net_addr(subnet_t* subnet, const address_t net_addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		strcpy(subnet->net_addr.addr[i], net_addr.addr[i]);
	}
}

char** get_host_range(subnet_t subnet) {
	return subnet.host_range;
}

void set_host_range(subnet_t* subnet, const char** host_range) {
	subnet->host_range = calloc(subnet->num_subnet, sizeof(char*));
	for (size_t i = 0; i < subnet->num_subnet; i++) {
		subnet->host_range[i] = calloc(strlen(host_range[i]) + 1, sizeof(char));
		strcpy(subnet->host_range[i], host_range[i]);
	}
}

char* get_broadcast_addr(subnet_t subnet) {
	return subnet.broadcast_addr;
}

void set_broadcast_addr(subnet_t* subnet, const char* broadcast_addr) {
	subnet->broadcast_addr = calloc(strlen(broadcast_addr) + 1, sizeof(char));
	strcpy(subnet->broadcast_addr, broadcast_addr);
}
