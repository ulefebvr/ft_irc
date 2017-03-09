#include <string.h>

#include "server.h"

static void		initiate_all_fd(t_server *server)
{
	int			i;

	i = 0;
	FD_ZERO(&server->rfds);
	FD_ZERO(&server->wfds);
	while (i < server->maxfds)
	{
		if (server->fds[i].type != FD_FREE)
		{
			FD_SET(i, &server->rfds);
			if (strlen(server->fds[i].buf_write) > 0)
			{
				FD_SET(i, &server->wfds);
			}
			server->max = i;
		}
		i++;
	}
}

void			server_loop(t_server *server)
{
	while (1)
	{
		initiate_all_fd(server);
		server->check = select(
			server->max + 1, &server->rfds, &server->wfds, NULL, NULL);
		if (server->check == -1)
		{
			// server_clean_exit(server);
			exit_on("select", __FILE__, __LINE__);
		}
		server_handle_io(server);
	}
}