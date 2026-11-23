#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/utils.h"
#include "../include/ipv4.h"
#include "../include/subnet.h"
#include "../include/input_handler.h"

//char* get_binary_ip_adress(char* ipv4_t);
//char* get_decimal_address(char* binary_address);
//bool check_cidr_address(char *cidr_address);
//bool check_ipv4_t(char *address_ip);
//char* get_subnet_mask(char *cidr_address);
//char* ipv4_t_input();
//char* cidr_address_input();
//int subnet_number_input();
//int* host_subnet_input(int subnet_number);
//int* array_order_desc(int* array, int array_length);
//struct ipv4_t get_subnet_address(int n_host_subnet, struct ip_address address_ip, char** prev_subnet, int array_length);
//struct addressing_scheme do_addressing(struct ipv4_t);

int main()
{
	ipv4_t address;
	memset(&address, 0, sizeof(ipv4_t));
	ip_address_input(&address.addr);
	address.cidr = cidr_input();
	compute_sub_mask(&address);
	size_t num_subnet = num_subnet_input();
	int* num_host = num_host_subnet_input(num_subnet);
	print_ipv4_scheme(address);

	return 0;
}

