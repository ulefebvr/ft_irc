#include <string.h>

#include "server.h"
#include "libft.h"

static void		send_informations(t_server *server, int cs, char *tmp)
{
	int			i;
	int			count;

	i = -1;
	count = 0;
	while (++i < server->maxfds)
	{
		if (i != cs && server->fds[i].type != FD_FREE && server->fds[cs].channel
			&& server->fds[cs].channel->id == server->fds[i].channel->id)
		{
			ft_strcpy(tmp + strlen(tmp), server->fds[i].nickname);
			ft_strcpy(tmp + strlen(tmp), " ");
			if (count++ == 20)
			{
				server_valid_respond(&server->fds[cs], tmp);
				ft_bzero(tmp, 512);
				count = 0;
			}
		}
	}
	if (strlen(tmp) > 0)
		server_valid_respond(&server->fds[cs], tmp);
}

void			server_client_who(t_server *server, int cs, t_header *msg)
{
	if (server->fds[cs].channel == NULL)
	{
		server_invalid_respond(&server->fds[cs],
			"Error, you are not within any channel.")
	}
	ft_bzero(msg->msg, 512);
	send_informations(server, cs, msg->msg);
}
