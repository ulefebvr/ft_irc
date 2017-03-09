#include <stdio.h>

#include "server.h"

void			server_client_leave(t_server *server, int cs, t_header *msg)
{
	(void)msg;
	printf("LEAVE     #%d[%s] leave [%s]channel\n",
		cs, server->fds[cs].nickname,
		server->fds[cs].channel ? server->fds[cs].channel->name : "unexist");
	server->fds[cs].channel = NULL;
}
