#include "../include/subnet.h"
#include <math.h>

ipv4_t get_net_addr(subnet_t subnet) {
	return subnet.net_addr;
}

void set_net_addr(subnet_t* subnet, const ipv4_t net_addr) {
	set_addr(&subnet->net_addr, net_addr.addr);
	set_cidr(&subnet->net_addr, net_addr.cidr);
	set_sub_mask(&subnet->net_addr, net_addr.sub_mask);
}

size_t get_num_addr(subnet_t subnet) {
	return subnet.num_addr;
}

void set_num_addr(subnet_t* subnet, size_t num_addr) {
	subnet->num_addr = num_addr;
}

address_t* get_host_range(subnet_t subnet) {
	return subnet.host_range;
}

void set_host_range(subnet_t* subnet) {
	subnet->host_range = calloc(subnet->num_addr - 2, sizeof(address_t));
	subnet->host_range[0] = get_next_address(subnet->net_addr.addr);
	for (size_t i = 1; i < subnet->num_addr - 2; i++) {
		subnet->host_range[i] = get_next_address(subnet->host_range[i - 1]);
	}
}

address_t get_broadcast_addr(subnet_t subnet) {
	return subnet.broad_addr;
}

void set_broadcast_addr(subnet_t* subnet) {
	subnet->broad_addr = get_next_address(subnet->host_range[subnet->num_addr - 3]);
}

void change_cidr(subnet_t* subnet, size_t n_host_bit) {
	if (!subnet || n_host_bit > TOTAL_SIZE_IPV4) {
  	return;
  }

  size_t old_cidr = get_cidr(subnet->net_addr);
  size_t new_cidr = TOTAL_SIZE_IPV4 - n_host_bit;

  if (new_cidr < old_cidr) {
  	return;
  }

  set_cidr(&subnet->net_addr, new_cidr);
}

bool subnet_create(subnet_t* subnet, address_t start, size_t n_host_bit) {
	memset(subnet, 0, sizeof(subnet_t));
	set_num_addr(subnet, (size_t) pow(2.0, (double) n_host_bit));

	subnet->host_range = calloc(subnet->num_addr - 2, sizeof(address_t));
	if (!subnet->host_range) return false;

	subnet->net_addr.addr = start;
	change_cidr(subnet, n_host_bit);
	compute_sub_mask(&subnet->net_addr);
	set_host_range(subnet);
	set_broadcast_addr(subnet);
	return true;
}

void subnet_destroy(subnet_t* subnet) {
	free(subnet->host_range);
	subnet->host_range = NULL;
	subnet->num_addr = 0;
}

void print_scheme(subnet_t subnet) {
	printf("Network address: ");
	print_address(subnet.net_addr.addr);
	printf("/%zu\nSubnet mask: ", subnet.net_addr.cidr);
	print_address(subnet.net_addr.sub_mask);
	printf("\nAddresses: %zu (%zu usable)\n", subnet.num_addr, subnet.num_addr - 2);
	for (size_t i = 0; i < subnet.num_addr - 2; i++) {
		print_address(subnet.host_range[i]);
		printf("\n");
	}
	printf("Broadcast address: ");
	print_address(subnet.broad_addr);
	printf("\n");
}
