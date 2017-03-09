#include "server.h"
#include "libft.h"

#include <sys/resource.h>

void		initiate_limits(t_server *server)
{
	int				i;
	struct rlimit	rlp;

	i = 0;
	if (-1 == getrlimit(RLIMIT_NOFILE, &rlp))
	{
		exit_on("getrlimit", __FILE__, __LINE__);
	}
	server->maxfds = rlp.rlim_cur;
	server->fds = (t_fd *)ft_memalloc(sizeof(t_fd) * server->maxfds);
	if (server->fds == NULL)
	{
		exit_on("malloc", __FILE__, __LINE__);
	}
	while (i < server->maxfds)
	{
		server_clean_fd(&server->fds[i]);
		i++;
	}
}

int			main(int ac, char **av)
{
	t_server		server;

	ft_bzero(&server, sizeof(t_server));
	initiate_limits(&server);
	server_getinfo(&server, ac, av);
	server_launch(&server);
	server_loop(&server);
	return (EXIT_SUCCESS);
}
