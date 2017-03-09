#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include "server.h"
#include "libft.h"

static void		client_exit(t_server *server, int cs)
{
	close(cs);
	printf("\033[31mQUIT      Client #%d[%s] deconnected\033[0m\n",
		cs, server->fds[cs].nickname);
	server_clean_fd(&server->fds[cs]);
}

void			treat_message(t_server *server, int cs, t_header *msg)
{
	if (msg->cmd == NICK)
		server_client_nick(server, cs, msg);
	else if (msg->cmd == JOIN)
		server_client_join(server, cs, msg);
	else if (msg->cmd == MSG)
		server_client_msg(server, cs, msg);
	else if (msg->cmd == LEAVE)
		server_client_leave(server, cs, msg);
	else if (msg->cmd == WHO)
		server_client_who(server, cs, msg);
}

void			client_read(t_server *server, int cs)
{
	int		size;

	size = recv(cs, server->fds[cs].buf_read + server->fds[cs].buffered,
		BUF_SIZE - server->fds[cs].buffered, 0);
	server->fds[cs].buffered += size;
	printf("RECV      Message from #%d[%s]\n", cs, server->fds[cs].nickname);
	if (size <= 0)
	{
		client_exit(server, cs);
	}
	else if (server->fds[cs].buffered >= sizeof(t_header))
	{
		treat_message(server, cs, (t_header *)server->fds[cs].buf_read);
		server->fds[cs].buffered -= sizeof(t_header);
		ft_memcpy(server->fds[cs].buf_read, server->fds[cs].buf_read
			+ sizeof(t_header), server->fds[cs].buffered);
	}
}

void		client_write(t_server *server, int cs)
{
	send(cs, server->fds[cs].buf_write, sizeof(t_header), 0);
	ft_bzero(server->fds[cs].buf_write, sizeof(t_header) + 1);
}
