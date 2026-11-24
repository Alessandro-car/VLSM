#include "../include/input_handler.h"

static bool read_int(const char* prompt, long min, long max, int* out) {
	char line[64];

	for (;;) {
		printf("%s", prompt);
		if (!fgets(line, sizeof line, stdin)) return false;

		char* end;
		errno = 0;
		long value = strtol(line, &end, 10);
		bool parsed = end != line && errno != ERANGE;
		while (isspace((unsigned char) *end)) end++;

		if (parsed && *end == '\0' && value >= min && value <= max) {
			*out = (int) value;
			return true;
		}
		printf("Invalid input. Enter an integer between %ld and %ld.\n", min, max);
	}
}

bool ip_address_input(address_t* addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		char prompt[40];
		snprintf(prompt, sizeof prompt, "Insert the octet n. %d: ", i + 1);
		if (!read_int(prompt, 0, 255, &addr->addr[i])) return false;
	}
	return true;
}

bool cidr_input(size_t* cidr) {
	int value;
	if (!read_int("Enter the CIDR address: /", 0, 30, &value)) return false;
	*cidr = (size_t) value;
	return true;
}

bool num_subnet_input(size_t* num_subnet) {
	int value;
	if (!read_int("Insert the number of the subnets: ", 1, MAX_SUBNETS, &value)) return false;
	*num_subnet = (size_t) value;
	return true;
}

int* num_host_subnet_input(size_t num_subnet) {
	int* num_hosts = calloc(num_subnet, sizeof(int));
	if (!num_hosts) return NULL;

	for (size_t i = 0; i < num_subnet; i++) {
		char prompt[64];
		snprintf(prompt, sizeof prompt, "Insert the number of hosts for subnet %zu: ", i + 1);
		if (!read_int(prompt, 1, INT_MAX, &num_hosts[i])) {
			free(num_hosts);
			return NULL;
		}
	}
	return num_hosts;
}
