#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define LOG_ERR(message) printf("%s%s%s", ANSI_COLOR_RED, message, ANSI_COLOR_RESET)

void reverse(char s[])
{
	int i, j;
  char c;

  for (i = 0, j = strlen(s)-1; i<j; i++, j--)
	{
  	c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

//Function to convert an integer to an array of chars
void itoa(int n, char s[])
{
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

char* get_binary_number(int number, int n_bits)
{

	char* bits = calloc(n_bits, sizeof(char));
	int *rem = calloc(1024, sizeof(int));
	int index = 0;

	while(number > 0)
	{
		rem[index] = number % 2;
		number /= 2;
		++index;
	}

	while(index < n_bits)
	{
		rem[index] = 0;
		++index;
	}

	for(int i = index - 1; i >= 0; --i)
	{
		bits[n_bits - 1 - i] = rem[i] + '0';
	}

	return bits;
}

void clear_stdin_buffer();

typedef struct ip_address
{
	char *address;
	char *cidr_address;
	char *subnet_mask;
} ip_address;

typedef struct addressing_scheme
{
    char *net_address;
    char **host_addresses;
    char *broadcast_address;
} addressing_scheme;

char* get_binary_ip_adress(char* ip_address);
char* get_decimal_address(char* binary_address);
bool check_cidr_address(char *cidr_address);
bool check_ip_address(char *address_ip);
char* get_subnet_mask(char *cidr_address);
char* ip_address_input();
char* cidr_address_input();
int subnet_number_input();
int* host_subnet_input(int subnet_number);
int* array_order_desc(int* array, int array_length);
struct ip_address get_subnet_address(int n_host_subnet, struct ip_address address_ip, char** prev_subnet, int array_length);
struct addressing_scheme do_addressing(struct ip_address);

int main()
{
	ip_address address_ip = { NULL, NULL, NULL };
	int subnet_numbers = 0;

	printf("%sTODO: A menu to communicate to the users the information to continue%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
	address_ip.address = ip_address_input();
	address_ip.cidr_address = cidr_address_input();
	address_ip.subnet_mask = get_subnet_mask(address_ip.cidr_address);
	subnet_numbers = subnet_number_input();
	int *host_number = calloc(subnet_numbers, sizeof(int));
	host_number = host_subnet_input(subnet_numbers);

	//char* subnet_address = calloc(255, sizeof(char));
	//subnet_address = "";
	int* ordered_array = calloc(subnet_numbers, sizeof(int));
	ordered_array = array_order_desc(host_number, subnet_numbers);

	char **prev_subnet = calloc(subnet_numbers, sizeof(char*));
	for(int i = 0; i < subnet_numbers; ++i)
		prev_subnet[i] = calloc(255, sizeof(char));

	ip_address subnet_address = { NULL , NULL , NULL };

	for(int i = 0; i < subnet_numbers; ++i)
	{
		subnet_address = get_subnet_address(ordered_array[i], address_ip, prev_subnet, subnet_numbers);
		printf("Address for the subnet n. %d: %s%s ----- Subnet mask: %s\n", (i + 1), subnet_address.address, subnet_address.cidr_address, subnet_address.subnet_mask);
		prev_subnet[i] = subnet_address.address;
	}


	return 0;
}

void clear_stdin_buffer()
{
	int c;
	while((c = getchar()) != '\n' && c != EOF) {}
}

char* insert_dots_address(char* address, int first_octet_bits, int second_octet_bits, int third_octet_bits, int fourth_octet_bits)
{
	char* get_address_dots = calloc(255, sizeof(char));
	strncpy(get_address_dots, address, first_octet_bits);
	get_address_dots[first_octet_bits] = '.';
	strncpy(&get_address_dots[first_octet_bits + 1], address + first_octet_bits, second_octet_bits);
	get_address_dots[first_octet_bits + second_octet_bits + 1] = '.';
	strncpy(&get_address_dots[first_octet_bits + second_octet_bits + 2], address + first_octet_bits + second_octet_bits, third_octet_bits);
	get_address_dots[first_octet_bits + second_octet_bits + third_octet_bits + 2] = '.';
	strncpy(&get_address_dots[first_octet_bits + second_octet_bits + third_octet_bits + 3], address + first_octet_bits + second_octet_bits + third_octet_bits, fourth_octet_bits);

	return get_address_dots;
}

char* get_binary_ip_address(char* ip_address)
{
	char* binary_ip_address = calloc(255, sizeof(char));
	char* splitted_ip = strtok(ip_address, ".");
	int n_octet = 0;

	char* bits = calloc(8, sizeof(char));
	while(splitted_ip != NULL)
	{
		int octet = atoi(splitted_ip);
		int *binary_number = calloc(8, sizeof(int));
		int index = 0;

		while(octet > 0)
		{
			binary_number[index] = octet % 2;
			octet /= 2;
			++index;
		}

		while(index < 8)
		{
			binary_number[index] = 0;
			++index;
		}

		for(int i = index - 1; i >= 0; --i)
		{
			bits[7 - i] = binary_number[i] + '0';
		}

		strncpy(&binary_ip_address[n_octet * 8], bits, strlen(bits));
		splitted_ip = strtok(NULL, ".");
		++n_octet;
	}
	return binary_ip_address;
}

char* get_decimal_address(char* binary_address)
{
	char* decimal_address = calloc(255, sizeof(char));
	char* splitted_address = strtok(binary_address, ".");
	int decimal_number = 0;
	char* decimal_value = calloc(3, sizeof(char));
	int prev_n_bits = 0;
	int n_octet = 0;

	int first_octet_bits = 0, second_octet_bits = 0, third_octet_bits = 0, fourth_octet_bits = 0;
	while(splitted_address != NULL)
	{
		decimal_number = 0;
		for(int i = 0; i < 8; ++i)
		{
			int value = splitted_address[i] - 48;
			decimal_number += (pow(2, 7 - i) * value);
		}
		itoa(decimal_number, decimal_value);
		strncpy(&decimal_address[prev_n_bits], decimal_value, strlen(decimal_value));
		splitted_address = strtok(NULL, ".");
		prev_n_bits += strlen(decimal_value);

		if(n_octet == 0)
			first_octet_bits = strlen(decimal_value);
		if(n_octet == 1)
			second_octet_bits = strlen(decimal_value);
		if(n_octet == 2)
			third_octet_bits = strlen(decimal_value);
		if(n_octet == 3)
			fourth_octet_bits = strlen(decimal_value);
		++n_octet;
	}

	char* get_decimal_address = insert_dots_address(decimal_address, first_octet_bits, second_octet_bits, third_octet_bits, fourth_octet_bits);


	return get_decimal_address;
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

bool check_ip_address(char* address_ip)
{
	char* ip_address = strncpy(ip_address, address_ip, strlen(address_ip));

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

	char* get_subnet = insert_dots_address(subnet_mask, 8, 8, 8, 8);

	return get_subnet;
}

char* ip_address_input()
{
	char* ip_address = calloc(1024, sizeof(char));
	int right_input = 0;
	do
	{
		printf("Type the IP address: ");
		size_t address_size = 0;
		getline(&ip_address, &address_size, stdin);
		ip_address[strlen(ip_address) - 1] = 0;
		right_input = check_ip_address(ip_address);
		if(right_input == 0)
			LOG_ERR("Wrong IP address!\nTry again!\n");

	}while(right_input != 1);

	return ip_address;
	free(ip_address);
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
		}while(right_input != 1);	}

	return host_number;
}

int* array_order_desc(int* array, int array_length)
{
	for(int i = 0; i < array_length; ++i)
	{
		for(int j = i + 1; j < array_length; ++j)
		{
			if(array[i] < array[j])
			{
				int greater = array[j];
				array[j] = array[i];
				array[i] = greater;
			}
		}
	}
	return array;
}
//TODO funziona ma devo aggiustare la questione degli indirizzi ripetuti, avviare per vedere
struct ip_address get_subnet_address(int n_host_subnet, struct ip_address address_ip, char** prev_subnet, int array_length)
{
	struct ip_address subnet_address;
	subnet_address.address = calloc(255, sizeof(char));
	subnet_address.cidr_address = calloc(3, sizeof(char));
	subnet_address.subnet_mask = calloc(255, sizeof(char));

	char* ip_address = calloc(255, sizeof(char));
	strncpy(ip_address, address_ip.address, strlen(address_ip.address));

	char** previous_subnet = calloc(array_length, sizeof(char*));

	for(int i = 0; i < array_length; ++i)
	{
		previous_subnet[i] = calloc(255, sizeof(char));
		strncpy(previous_subnet[i], prev_subnet[i], strlen(prev_subnet[i]));
	}

	char* cidr_number = calloc(2, sizeof(char));
	strncpy(cidr_number, address_ip.cidr_address + 1, 2);
	int n_network_bits = atoi(cidr_number);

	char* binary_ip = calloc(255, sizeof(char));
	binary_ip = get_binary_ip_address(ip_address);

	int n_dots = 0;
	if(n_network_bits >= 8)
		n_dots = 1;
	if(n_network_bits >= 16)
		n_dots = 2;
	if(n_network_bits >= 24)
		n_dots = 3;

	char* host_portion = memset(binary_ip + n_network_bits + n_dots, '0', 32 - n_network_bits - n_dots);
	int necessary_host_bit = ceil(log(n_host_subnet + 2) / log(2));
	int max_n_subnet = pow(2, (32 - n_network_bits - necessary_host_bit));

	char* extra_network_portion = calloc(32, sizeof(char));
	strncpy(extra_network_portion, host_portion, (32 - n_network_bits - necessary_host_bit));
	int decimal_network_portion = atoi(extra_network_portion);

	char* address_subnet = calloc(255, sizeof(char));
	bool new_subnet = false;

	int cidr_address_subnet_number = 0;

	char* cidr_address_subnet = calloc(3, sizeof(char));
	cidr_address_subnet[0] = '/';
	char* cidr_subnet_number = calloc(2, sizeof(char));
	for(int i = 0; i < max_n_subnet; ++i)
	{
		strncpy(binary_ip + n_network_bits, get_binary_number(decimal_network_portion, (32 - n_network_bits - necessary_host_bit)), (32 - n_network_bits - necessary_host_bit));
		strncpy(subnet_address.address, get_decimal_address(insert_dots_address(binary_ip, 8, 8, 8, 8)), strlen(get_decimal_address(insert_dots_address(binary_ip, 8, 8, 8, 8))));

		for(int i = 0; i < array_length; ++i)
		{
			if(strcmp(subnet_address.address, previous_subnet[i]) != 0)
			{
				new_subnet = true;
			} else if(strcmp(subnet_address.address, previous_subnet[i]) == 0)
			{
				new_subnet = false;
				break;
			}
		}
		decimal_network_portion++;

		if(new_subnet)
		{
			cidr_address_subnet_number = 32 - necessary_host_bit;
			itoa(cidr_address_subnet_number, cidr_subnet_number);
			strcat(cidr_address_subnet, cidr_subnet_number);
			subnet_address.cidr_address = cidr_address_subnet;
			subnet_address.subnet_mask = get_decimal_address(get_subnet_mask(subnet_address.cidr_address));
			break;
		}
	}
	return subnet_address;
}

struct addressing_scheme do_addressing(struct ip_address)
{
    struct addressing_scheme addressing_plan;
    addressing_plan.broadcast_address = calloc(255, sizeof(char));
    char* cidr_number = calloc(2, sizeof(char));
	strncpy(cidr_number, ip_address.cidr_address + 1, 2);
	int n_host_bits = 32 - atoi(cidr_number);
	
	int n_hosts = pow(2, n_host_bits) - 2;
	addressing_plan.host_addresses = calloc(n_hosts, sizeof(char*));
	
	for(int i = 0; i < n_hosts; ++i)
	{
	    addressing_plan.host_addresses[i] = calloc(255, sizeof(char));
	}
	
    strncpy(addressing_plan.net_address, ip_address.address, strlen(ip_address.address));
    //TODO host_addresses
    //TODO broadcast_address
}
