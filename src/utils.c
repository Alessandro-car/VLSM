#include "../include/utils.h"

void reverse(char* s) {
	int i, j;
	char c;

	for (i = 0; j = strlen(s) - 1, i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char* s) {
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

char* get_binary_number(int number, int n_bits) {
	char* bits = calloc(n_bits, sizeof(char));
	int* rem = calloc(1024, sizeof(int));
	int index = 0;

	while (number > 0) {
		rem[index] = number % 2;
		number /= 2;
		++index;
	}

	while (index < n_bits) {
		rem[index] = 0;
		++index;
	}

	for (int i = index - 1; i >= 0; --i) {
		bits[n_bits - 1 - i] = rem[i] + '0';
	}

	return bits;
}

void clear_stdin_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
