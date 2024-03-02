#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NEW_LINE printf("\n");
//TODO understand how to print error messages in red, like if it is a GUI
bool check_cidr_address(char *cidr_address)
{
	if(cidr_address[0] == '\0')
	{
		//TODO check input cidr
		printf("You didn't insert the CIDR address\n");
		return false;
	}

	if(cidr_address[0] != '/')
	{
		printf("The first character of the CIDR address must be '/'\n");
		return false;
	}

	if(strlen(cidr_address) > 3 || strlen(cidr_address) < 1)
	{
		printf("Check the input of the CIDR address\n");
		return false;
	}

	char *numbers = calloc(3, sizeof(char));
	strncpy(numbers, cidr_address + 1, 2);
	for(int i = 0; i < strlen(numbers); ++i)
	{ //TODO check_input
		if(!isdigit(numbers[i]))
		{
			printf("You must enter digits in the CIDR address\n");
			return false;
		}
	}

	if(atoi(numbers) < 1 || atoi(numbers) > 32)
	{
		printf("THe digits must be between 1 and 32\n");
		return false;
	}
	return true;
}

bool check_ip_address(char* ip_address)
{
  if(ip_address[0] == '\0')
	{
		//TODO check input
		printf("You didn't insert the IP address\n");
		return false;
	}

	char* splitted_ip = strtok(ip_address, ".");
	int octet = 0;
	while(splitted_ip != NULL)
	{
		for(int i = 0; i < strlen(splitted_ip); ++i)
		{
			if(!isdigit(splitted_ip[i]))
			{
				printf("You must enter digits!\n");
				return false;
			}
		}

		if(atoi(splitted_ip) < 0 || atoi(splitted_ip) > 255)
		{
			printf("The number must be between 0 and 255\n");
			return false;
		}
		splitted_ip = strtok(NULL, ".");
		++octet;
	}
	//TODO check_input
	if(octet != 4)
	{
		printf("Check the input of the IP address\n");
		return false;
	}

	return true;
}

char* get_subnet_mask(char* cidr_address)
{
	char* subnet_mask = calloc(255, sizeof(char));
	char* num_cidr_address = calloc(3, sizeof(char));
	strncpy(num_cidr_address, cidr_address + 1, 2);

	memset(subnet_mask, '1', atoi(num_cidr_address));
	memset(subnet_mask + atoi(num_cidr_address), '0', 32 - atoi(num_cidr_address));

	char* get_subnet = calloc(255, sizeof(char));
	strncpy(get_subnet, subnet_mask, 8);
	get_subnet[8] = '.';
	strncpy(&get_subnet[9], subnet_mask + 8, 8);
	get_subnet[16] = '.';
	strncpy(&get_subnet[17], subnet_mask + 16, 8);
	get_subnet[24] = '.';
	strncpy(&get_subnet[25], subnet_mask + 24, 8);

	return get_subnet;
}

int main()
{
	typedef struct ip_address
	{
		char *address;
		char *cidr_address;
		char *subnet_mask;
	} ip_address;

	ip_address network_address = { NULL, NULL, NULL };

	network_address.address = calloc(255, sizeof(char));
	network_address.cidr_address = calloc(3, sizeof(char));
	printf("TODO: A menu to communicate to the users the information to continue\n");
	printf("Type the IP address: ");
	size_t address_size = 0;
	getline(&network_address.address, &address_size, stdin);
	network_address.address[strlen(network_address.address) - 1] = 0;
	printf("Type the CIDR address: ");
	size_t cidr_address_size = 0;
	getline(&network_address.cidr_address, &cidr_address_size, stdin);
	network_address.cidr_address[strlen(network_address.cidr_address) - 1] = 0;
	if(check_cidr_address(network_address.cidr_address))
	{
		network_address.subnet_mask = get_subnet_mask(network_address.cidr_address);
		printf("%s\n", network_address.subnet_mask);
	}
	check_ip_address(network_address.address);

	int subnet_numbers = 0;
	//TODO check_input if the user enter letters or something else that is not a digit
	printf("Numbers of the subnet: ");
	scanf("%d", &subnet_numbers);

	int numbers_host[subnet_numbers];
	for(int i = 0; i < subnet_numbers; ++i)
	{
		//TODO check_input if the users enter letters or something else that is not a digit
		printf("Numbers of host for the subnet n. %d: ", (i + 1));
		scanf("%d", &numbers_host[i]);
	}

	free(network_address.address);
	free(network_address.cidr_address);
	return 0;
}
