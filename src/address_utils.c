#include "../include/address_utils.h"

void binary_to_dec_addr(char dec_addr[NUM_OCTETS][OCTET_DEC_SIZE], const char bin_addr[NUM_OCTETS][OCTET_BIT_SIZE]) {


}

void format_ipv4_addr(char* converted_addr, const char addr[NUM_OCTETS][OCTET_DEC_SIZE]) {
	char *p = converted_addr;

	for (int i = 0; i < NUM_OCTETS; i++) {
			size_t len = strlen(addr[i]);
			memcpy(p, addr[i], len);
			p += len;

			if (i < NUM_OCTETS - 1) {
					*p++ = '.';
			}
	}

	*p = '\0';
}
