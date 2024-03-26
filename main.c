#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define LOG_ERR(message) printf("%s%s%s", ANSI_COLOR_RED, message, ANSI_COLOR_RESET)

//TODO understand how to print error messages in red, like if it is a GUI

bool check_cidr_address(char *cidr_address);
bool check_ip_address(char *network_address);
char* get_subnet_mask(char *cidr_address);
char* ip_address_input();
char* cidr_address_input();
int subnet_number_input();
int* host_subnet_input(int subnet_number);
void clear_stdin_buffer();


int main()
{
	typedef struct ip_address
	{
		char *address;
		char *cidr_address;
		char *subnet_mask;
	} ip_address;
	ip_address network_address = { NULL, NULL, NULL };
	int subnet_numbers = 0;

	printf("%sTODO: A menu to communicate to the users the information to continue%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
	network_address.address = ip_address_input();
	network_address.cidr_address = cidr_address_input();
	network_address.subnet_mask = get_subnet_mask(network_address.cidr_address);
	subnet_numbers = subnet_number_input();

	int *host_number = calloc(subnet_numbers, sizeof(int));
	host_number = host_subnet_input(subnet_numbers);

	printf("%s\n%s\n%s\n%d\n", network_address.address, network_address.subnet_mask, network_address.cidr_address, subnet_numbers);

	for(int i = 0; i < subnet_numbers; ++i)
	{
		printf("%d\n", host_number[i]);
	}
	return 0;
}

void clear_stdin_buffer()
{
	int c;
	while((c = getchar()) != '\n' && c != EOF) {}
}

bool check_cidr_address(char *cidr_address)
{
	if (cidr_address[0] == '\0')
	{
		LOG_ERR("You didn't insert the CIDR address\n");
		return false;
	}

	if (cidr_address[0] != '/')
	{
		LOG_ERR("The first character of the CIDR address must be '/'\n");
		return false;
	}

	if (strlen(cidr_address) > 3 || strlen(cidr_address) < 1)
	{
		LOG_ERR("Check the input of the CIDR address\n");
		return false;
	}

	char *numbers = calloc(3, sizeof(char));
	strncpy(numbers, cidr_address + 1, 2);
	for(int i = 0; i < strlen(numbers); ++i)
	{
		if(!isdigit(numbers[i]))
		{
			LOG_ERR("You must enter digits in the CIDR address\n");
			return false;
		}
	}

	if(atoi(numbers) < 1 || atoi(numbers) > 32)
	{
		LOG_ERR("The digits must be between 1 and 32%s\n");
		return false;
	}

	return true;
}

bool check_ip_address(char* network_address)
{
	char* ip_address = strncpy(ip_address, network_address, strlen(network_address));

	if(ip_address[0] == '\0')
	{
		LOG_ERR("You didn't insert the IP address\n");
		return false;
	}

	if(ip_address[0] == '.' || ip_address[strlen(ip_address) - 1] == '.')
	{
		LOG_ERR("The first and the last character must be a number\n");
		return false;
	}


	for(int i = 0; i < strlen(ip_address); ++i)
	{
		if(ip_address[i] == '.' && ip_address[i + 1] == '.')
		{
			LOG_ERR("You must insert numbers between the dots!\n");
			return false;
		}
	}

	char* splitted_ip = strtok(ip_address, ".");
	if(splitted_ip == NULL)
	{
		LOG_ERR("You didn't insert the IP address\n");
		return false;
	}
	int dots = 0;
	while(splitted_ip != NULL)
	{
		for(int i = 0; i < strlen(splitted_ip); ++i)
		{
			if(!isdigit(splitted_ip[i]))
			{
				LOG_ERR("You must insert digits\n");
				return false;
			}
		}

		if(atoi(splitted_ip) >= 0 && atoi(splitted_ip) <= 255)
		{
			splitted_ip = strtok(NULL, ".");
			if(splitted_ip != NULL)
				++dots;
		} else
		{
			LOG_ERR("The number must be between 0 and 255\n");
			return false;
		}
	}


	if(dots != 3)
	{
		LOG_ERR("Check the input of the IP address\n");
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
	get_subnet[17] = '.';
	strncpy(&get_subnet[18], subnet_mask + 16, 8);
	get_subnet[26] = '.';
	strncpy(&get_subnet[27], subnet_mask + 24, 8);

	return get_subnet;
}

char* ip_address_input()
{
	char* network_address = calloc(1024, sizeof(char));
	int right_input = 0;
	do
	{
		printf("Type the IP address: ");
		size_t address_size = 0;
		getline(&network_address, &address_size, stdin);
		network_address[strlen(network_address) - 1] = 0;
		right_input = check_ip_address(network_address);
		if(right_input == 0)
			LOG_ERR("Wrong IP address!\nTry again!\n");

	}while(right_input != 1);

	return network_address;
	free(network_address);
}

char* cidr_address_input()
{
	char* cidr_address = calloc(3, sizeof(char));
	int right_input = 0;
	do
	{
		printf("Type the CIDR address: ");
		size_t cidr_address_size = 0;
		getline(&cidr_address, &cidr_address_size, stdin);
		cidr_address[strlen(cidr_address) - 1] = 0;
		right_input = check_cidr_address(cidr_address);
		if(right_input == 0)
		{
			LOG_ERR("Wrong CIDR address!\nTry again\n");
		}
	}while(right_input != 1);

	return cidr_address;
	free(cidr_address);
}

int subnet_number_input()
{
	int subnet_number = 0;
	int right_input = 0;

	do{

		printf("Number of the subnet: ");
		right_input = scanf("%d", &subnet_number);
		clear_stdin_buffer();

		if (right_input == 0)
			LOG_ERR("You have to insert numbers!\n");
	}while(right_input != 1);

	return subnet_number;
}

int* host_subnet_input(int subnet_number)
{
	int right_input = 0;
	int *host_number = calloc(subnet_number, sizeof(int));
	for(int i = 0; i < subnet_number; ++i)
	{
		do{
			printf("Numbers of host for the subnet n. %d: ", (i + 1));
			right_input = scanf("%d", &host_number[i]);
			clear_stdin_buffer();

			if(right_input == 0)
			{
				LOG_ERR("You have to insert numbers!\n");
			}
		}while(right_input != 1);
	}

	return host_number;
}
