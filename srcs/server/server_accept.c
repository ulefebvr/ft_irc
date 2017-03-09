#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"

static int		get_client_socket(t_server *server, int s)
{
	int						cs;
	struct sockaddr_in		csin;
	socklen_t				cslen;

	cslen = sizeof(struct sockaddr);
	cs = accept(s, (struct sockaddr *)&csin, &cslen);
	if (-1 == cs)
	{
		(void)server;
		// server_clean_exit(server); CLOSING ALL CLIENT FD
		exit_on("accept", __FILE__, __LINE__);
	}
	printf("\033[31;1mNew client #%d from %s:%d\n\033[0m",
		cs, inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	return (cs);
}

void			server_accept(t_server *server, int s)
{
	int			cs;

	cs = get_client_socket(server, s);
	server_clean_fd(&server->fds[cs]);
	server->fds[cs].type = FD_CLIENT;
	server->fds[cs].read = client_read;
	server->fds[cs].write = client_write;
}
