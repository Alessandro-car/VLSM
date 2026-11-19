#include "../include/input_handler.h"

//TODO: Insert check for input address input
void ip_address_input(char* addr) {
	printf("Insert the ip address: ");
	scanf("%s", addr);
	clear_stdin_buffer();
}

size_t cidr_input() {
	int cidr = -1;
	printf("Enter the CIDR address: /");
	while (cidr < 0 || cidr > 32) {
		scanf("%d", &cidr);
		if (cidr < 0 || cidr > 32) {
			printf("Invalid CIDR address. The value must be between 0 and 32.\n");
			printf("Enter the CIDR address: /");
		}
	}
	clear_stdin_buffer();
	return (size_t) cidr;
}

size_t num_subnet_input() {
	int num_subnet = -1;
	printf("Insert the number of the subnets: ");
	while (num_subnet < 0) {
		scanf("%d", &num_subnet);
		if (num_subnet < 0) {
			printf("Invalid number. The number must be greater than 0.\n");
			printf("Insert the number of the subnets: ");
		}
	}
	clear_stdin_buffer();
	return (size_t) num_subnet;
}

int* num_host_subnet_input(size_t num_subnet) {
	int* num_hosts = calloc(num_subnet, sizeof(int));
	for (size_t i = 0; i < num_subnet; i++) {
		printf("Insert the number of hosts for the %zu subnet: ", (i + 1));
		num_hosts[i] = -1;
		while (num_hosts[i] < 0) {
			scanf("%d", &num_hosts[i]);
			if (num_hosts[i] < 0) {
				printf("Invalid number. The number must be greater than 0.\n");
				printf("Insert the number of host for the %zu subnet: ", (i + 1));
			}
			clear_stdin_buffer();
		}
	}
	return num_hosts;
}
