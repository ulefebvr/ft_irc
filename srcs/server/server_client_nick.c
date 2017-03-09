#include <stdio.h>

#include "server.h"
#include "libft.h"

int			check_valid_nickname(t_server *server, int cs, char *nickname)
{
	int		i;

	i = 0;
	while (i < server->maxfds)
	{
		if (i != cs && server->fds[i].type != FD_FREE
			&& !ft_strncmp(nickname, server->fds[i].nickname, 20))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void		server_client_nick(t_server *server, int cs, t_header *msg)
{
	if (check_valid_nickname(server, cs, msg->from))
	{
		printf("\033[32;1mNICK      succes : #%d changed his nickname from "
			"%s to %s\n\033[0m", cs, server->fds[cs].nickname, msg->from);
		ft_strcpy(server->fds[cs].nickname, msg->from);
		server->fds[cs].auth = 1;
		server_valid_respond(&server->fds[cs], NULL);
	}
	else
	{
		printf("\033[31;1mNICK      error : #%d tried to change his nickname "
			"from %s to %s\n\033[0m", cs, server->fds[cs].nickname, msg->from);
		server_invalid_respond(&server->fds[cs],
			"This nickname is already used, please choose another one.");
	}
}
