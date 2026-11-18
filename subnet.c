#include "subnet.h"

char* get_net_addr(subnet_t subnet) {
	return subnet.net_addr;
}

void set_net_addr(subnet_t* subnet, const char* net_addr) {
	subnet->net_addr = calloc(strlen(net_addr) + 1, sizeof(char));
	strcpy(subnet->net_addr, net_addr);
}

char** get_host_range(subnet_t subnet) {
	return subnet.host_range;
}

void set_host_range(subnet_t* subnet, const char** host_range) {
	subnet->host_range = calloc(strlen(host_range) + 1, sizeof(char*));
	for (size_t i = 0; i < strlen(host_range); i++) {
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
