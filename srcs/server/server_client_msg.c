#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"
#include "libft.h"

#include <stdio.h>

void			public_message(t_server *server, int cs)
{
	int			i;

	i = 0;
	while (i < server->maxfds)
	{
		if (i != cs && server->fds[i].type != FD_FREE
			&& server->fds[i].channel && server->fds[cs].channel &&
			server->fds[i].channel->id == server->fds[cs].channel->id)
		{
			send(i, server->fds[cs].buf_read, sizeof(t_header), 0);
		}
		i++;
	}
}

void			private_message(t_server *server, int cs, t_header *msg)
{
	int			i;

	i = 0;
	while (i < server->maxfds)
	{
		if (i != cs && server->fds[i].type != FD_FREE &&
			!ft_strncmp(server->fds[i].nickname, msg->to, 20))
		{
			send(i, server->fds[cs].buf_read, sizeof(t_header), 0);
			server_valid_respond(&server->fds[cs], NULL);
			printf("\033[32;1mMSG       Message sent.\n\033[0m");
			return ;
		}
		i++;
	}
	printf("\033[31;1mMSG       The user %s doesn't exist.\n\033[0m", msg->to);
	server_invalid_respond(&server->fds[cs], "This user doesn't exist.");
}

void			server_client_msg(t_server *server, int cs, t_header *msg)
{
	if (msg->private_msg)
	{
		printf("MSG       Private message from [%s] to [%s]"
			"\n          \"%s\"\n",
			server->fds[cs].nickname, msg->to, msg->msg);
		private_message(server, cs, msg);
	}
	else
	{
		printf("MSG       Public message from [%s] to channel [%s]\n"
			"          \"%s\"\n", server->fds[cs].nickname,
			server->fds[cs].channel ? server->fds[cs].channel->name : "unexist",
			msg->msg);
		public_message(server, cs);
	}
}
