#include "../include/subnet.h"


bool subnet_create(subnet_t* subnet, address_t start, size_t n_host_bit) {
	memset(subnet, 0, sizeof(subnet_t));
	subnet->num_addr = (size_t) pow(2.0, (double) n_host_bit);

	subnet->host_range = calloc(subnet->num_addr - 2, sizeof(address_t));
	if (!subnet->host_range) return false;

	subnet->net_addr.addr = start;
	subnet->net_addr.cidr = TOTAL_SIZE_IPV4 - n_host_bit;
	compute_sub_mask(&subnet->net_addr);
	subnet->host_range[0] = get_next_address(start);
	for (size_t i = 1; i < subnet->num_addr - 2; i++) {
		subnet->host_range[i] = get_next_address(subnet->host_range[i - 1]);
	}
	subnet->broad_addr = get_next_address(subnet->host_range[subnet->num_addr - 3]);
	return true;
}

void subnet_destroy(subnet_t* subnet) {
	free(subnet->host_range);
	subnet->host_range = NULL;
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
