#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char*  net_addr;
	size_t num_subnet;
	char** host_range;
	char*  broadcast_addr;
} subnet_t;

char* get_net_addr(subnet_t subnet);
void set_net_addr(subnet_t* subnet, const char* net_addr);
char** get_host_range(subnet_t subnet);
void set_host_range(subnet_t* subnet, const char** host_range);
char* get_broadcast_addr(subnet_t subnet);
void set_broadcast_addr(subnet_t* subnet, const char* broadcast_addr);
