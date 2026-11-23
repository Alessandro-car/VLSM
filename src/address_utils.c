#include "../include/address_utils.h"

void binary_to_dec_addr(address_t* dec_addr, const address_t bin_addr) {
	for (int i = 0; i < NUM_OCTETS; i++) {
		octet_to_decimal_str(bin_addr.addr[i], dec_addr->addr[i], OCTET_DEC_SIZE + 1);
	}
}

void octet_to_decimal_str(const char octet[OCTET_BIT_SIZE + 1], char* out, size_t out_size) {
	if (!octet || !out || out_size == 0)
		return;
	uint8_t val = 0;
	for (int i = 0; i < OCTET_BIT_SIZE; i++) {
		val = (uint8_t)((val << 1) | (uint8_t)(octet[i] == '1'));
	}
	snprintf(out, out_size, "%u", (unsigned int)val);
}
