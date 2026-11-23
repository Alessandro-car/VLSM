#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/utils.h"
#include "../include/ipv4.h"
#include "../include/subnet.h"
#include "../include/input_handler.h"

//TODO: Perform subnetting

int main()
{
	ipv4_t address;
	subnet_t* subnet;
	size_t num_subnet;
	int* num_host;

	//subnet_scheme.host_range;
	//subnet_scheme.broadcast_addr;
	//subnet_scheme.net_addr

	memset(&address, 0, sizeof(ipv4_t));
	ip_address_input(&address.addr);
	address.cidr = cidr_input();
	compute_sub_mask(&address);
	num_subnet = num_subnet_input();
	subnet = calloc(num_subnet, sizeof(subnet_t));
	for (int i = 0; i < num_subnet; i++) {
		memset(&subnet[i], 0, sizeof(subnet_t));
	}
	num_host = num_host_subnet_input(num_subnet);
	quicksort_desc(num_host, 0, num_subnet - 1);
	print_ipv4_scheme(address);
	for (int i = 0; i < num_subnet; i++) {
		set_net_addr(&subnet[i], address);
		set_num_host(&subnet[i], num_host[i]);
		change_cidr(&subnet[i], get_num_host(subnet[i]));
		compute_sub_mask(&subnet[i].net_addr);
		set_host_range(&subnet[i]);
		set_broadcast_addr(&subnet[i]);
		print_scheme(subnet[i]);
		printf("\n\n");
		address.addr = get_next_address(get_broadcast_addr(subnet[i]));
		compute_sub_mask(&address);
		set_cidr(&address, get_cidr(get_net_addr(subnet[i])));
	}


	return 0;
}

