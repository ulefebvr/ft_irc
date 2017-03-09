#include "server.h"
#include "libft.h"

#include <stdio.h>

t_channel		*channel_exist(t_server *server, char *channel_name)
{
	t_channel		*tmp;

	tmp = server->channel_list;
	while (tmp)
	{
		if (!ft_strcmp(channel_name, tmp->name))
		{
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

t_channel		*create_channel(t_server *server, char *channel_name)
{
	static int		id = 0;
	t_channel		*new;

	if ((new = (t_channel *)ft_memalloc(sizeof(t_channel))))
	{
		new->id = id++;
		ft_strcpy(new->name, channel_name);
		new->next = server->channel_list;
		server->channel_list = new;
	}
	return (new);
}

void			server_client_join(t_server *server, int cs, t_header *msg)
{
	t_channel	*channel;

	if (!(channel = channel_exist(server, msg->msg + 6)))
	{
		if (!(channel = create_channel(server, msg->msg + 6)))
		{
			server_invalid_respond(
				&server->fds[cs], "Unable to create this channel");
			return ;
		}
		server->fds[cs].channel = channel;
		printf("JOIN      #%d[%s] created the channel [%s]\n",
			cs, server->fds[cs].nickname, channel->name);
		server_valid_respond(
			&server->fds[cs], "New channel was created");
	}
	else
	{
		server->fds[cs].channel = channel;
		printf("JOIN      #%d[%s] joined the channel [%s]\n",
				cs, server->fds[cs].nickname, channel->name);
		server_valid_respond(
			&server->fds[cs], "You have joined the channel");
	}
}
