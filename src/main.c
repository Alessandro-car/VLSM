#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/ipv4.h"
#include "../include/subnet.h"
#include "../include/input_handler.h"

int main(void) {
	ipv4_t address = { 0 };
	size_t num_subnet;

	if (!ip_address_input(&address.addr) ||
	    !cidr_input(&address.cidr) ||
	    !num_subnet_input(&num_subnet)) {
		fprintf(stderr, "Input error.\n");
		return EXIT_FAILURE;
	}

	int* num_host = num_host_subnet_input(num_subnet);
	if (!num_host) {
		fprintf(stderr, "Input error.\n");
		return EXIT_FAILURE;
	}

	subnet_t* subnet = calloc(num_subnet, sizeof(subnet_t));
	if (!subnet) {
		free(num_host);
		return EXIT_FAILURE;
	}

	quicksort_desc(num_host, 0, (int) num_subnet - 1);

	const address_t given = address.addr;
	compute_net_addr(&address);
	if (memcmp(&given, &address.addr, sizeof(address_t)) != 0) {
		printf("Host bits cleared, using network address ");
		print_address(address.addr);
		printf("/%zu\n", address.cidr);
	}
	printf("\n");

	uint64_t remaining = 1ULL << (TOTAL_SIZE_IPV4 - address.cidr);
	address_t next = address.addr;
	size_t created = 0;
	int status = EXIT_SUCCESS;

	for (size_t i = 0; i < num_subnet; i++) {
		const size_t n_bit_host = compute_n_host_bit(num_host[i]);
		const uint64_t size = 1ULL << n_bit_host;

		if (size > remaining) {
			fprintf(stderr, "Not enough space left for the subnet with %d hosts.\n", num_host[i]);
			status = EXIT_FAILURE;
			break;
		}
		if (!subnet_create(&subnet[i], next, n_bit_host)) {
			fprintf(stderr, "Out of memory for the subnet with %d hosts.\n", num_host[i]);
			status = EXIT_FAILURE;
			break;
		}
		created++;

		print_scheme(subnet[i]);
		printf("\n");

		next = get_next_address(subnet[i].broad_addr);
		remaining -= size;
	}

	for (size_t i = 0; i < created; i++) {
		subnet_destroy(&subnet[i]);
	}
	free(subnet);
	free(num_host);

	return status;
}
