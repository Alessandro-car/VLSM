#include "../include/subnet.h"

ipv4_t get_net_addr(subnet_t subnet) {
	return subnet.net_addr;
}

void set_net_addr(subnet_t* subnet, const ipv4_t net_addr) {
	set_addr(&subnet->net_addr, net_addr.addr);
	set_cidr(&subnet->net_addr, net_addr.cidr);
	set_sub_mask(&subnet->net_addr, net_addr.sub_mask);
}

size_t get_num_host(subnet_t subnet) {
	return subnet.num_host;
}

void set_num_host(subnet_t* subnet, size_t num_host) {
	subnet->num_host = num_host;
}

address_t* get_host_range(subnet_t subnet) {
	return subnet.host_range;
}

void set_host_range(subnet_t* subnet) {
	subnet->host_range = calloc(subnet->num_host, sizeof(address_t));
	subnet->host_range[0] = get_next_address(subnet->net_addr.addr);
	for (size_t i = 1; i < subnet->num_host; i++) {
		subnet->host_range[i] = get_next_address(subnet->host_range[i - 1]);
	}
}

address_t get_broadcast_addr(subnet_t subnet) {
	return subnet.broad_addr;
}

void set_broadcast_addr(subnet_t* subnet) {
	subnet->broad_addr = get_next_address(subnet->host_range[subnet->num_host - 1]);
}

size_t compute_n_host_bit(subnet_t subnet) {
	return (size_t) ceil(log2((double) get_cidr(subnet.net_addr)));
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

void print_scheme(subnet_t subnet) {
	print_ipv4_scheme(subnet.net_addr);
	printf("\nNum host: %zu", subnet.num_host);
	for (size_t i = 0; i < subnet.num_host; i++) {
		print_address(subnet.host_range[i]);
		printf("\n");
	}
	print_address(subnet.broad_addr);
}
