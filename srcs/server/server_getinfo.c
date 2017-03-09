#include "server.h"

#include <stdlib.h>
#include <stdio.h>


void			server_getinfo(t_server *server, int ac, char **av)
{
	int			port;

	if (ac != 2)
	{
		fprintf(stderr, "./server port\n");
		exit(1);
	}
	else if (ac == 2)
	{
		port = atoi(av[1]);
		server->port = port;
	}
	else
	{
		fprintf(stderr, "./server port\n");
		exit(1);
	}
}
