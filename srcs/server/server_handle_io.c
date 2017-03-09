#include <sys/select.h>

#include "server.h"


#include <stdio.h>
void		server_handle_io(t_server *server)
{
	int			i;

	i = 0;
	while (i < server->maxfds && server->check > 0)
	{
		if (FD_ISSET(i, &server->rfds))
		{
			server->fds[i].read(server, i);
			server->check--;
		}
		if (FD_ISSET(i, &server->wfds))
		{
			server->fds[i].write(server, i);
			server->check--;
		}
		i++;
	}
}
