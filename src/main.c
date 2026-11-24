#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/utils.h"
#include "../include/ipv4.h"
#include "../include/subnet.h"
#include "../include/input_handler.h"

int main()
{
	ipv4_t address;
	subnet_t* subnet;
	size_t num_subnet;
	int* num_host;
	size_t n_bit_host;

	memset(&address, 0, sizeof(ipv4_t));
	ip_address_input(&address.addr);
	address.cidr = cidr_input();
	compute_sub_mask(&address);
	num_subnet = num_subnet_input();
	subnet = calloc(num_subnet, sizeof(subnet_t));
	for (size_t i = 0; i < num_subnet; i++) memset(&subnet[i], 0, sizeof(subnet_t));
	if (!subnet) return 1;
	num_host = num_host_subnet_input(num_subnet);
	if (!num_host) {
		free(subnet);
		return 1;
	}

	quicksort_desc(num_host, 0, (int) num_subnet - 1);
	for (size_t i = 0; i < num_subnet; i++) {
		set_net_addr(&subnet[i], address);
		n_bit_host = compute_n_host_bit(num_host[i]);
		set_num_host(&subnet[i], (size_t) pow(2.0, (double) n_bit_host));
		change_cidr(&subnet[i], n_bit_host);
		compute_sub_mask(&subnet[i].net_addr);
		set_host_range(&subnet[i]);
		set_broadcast_addr(&subnet[i]);
		print_scheme(subnet[i]);
		printf("\n\n");

		address.addr = get_next_address(get_broadcast_addr(subnet[i]));
		set_cidr(&address, get_cidr(get_net_addr(subnet[i])));
		compute_sub_mask(&address);
	}

	for (size_t i = 0; i < num_subnet; i++) {
		free(subnet[i].host_range);
	}
	free(subnet);
	free(num_host);

	return 0;
}

