#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"

static int		create_socket(void)
{
	int						s;
	struct protoent			*pe;

	if (NULL == (pe = getprotobyname("tcp")))
	{
		exit_on("getprotobyname", __FILE__, __LINE__);
	}
	if (-1 == (s = socket(AF_INET, SOCK_STREAM, pe->p_proto)))
	{
		exit_on("socket", __FILE__, __LINE__);
	}
	return (s);
}

void			server_launch(t_server *server)
{
	int						s;
	struct sockaddr_in		sin;

	s = create_socket();
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(server->port);
	if (-1 == bind(s, (struct sockaddr *)&sin, sizeof(sin)))
	{
		exit_on("bind", __FILE__, __LINE__);
	}
	if (-1 == listen(s, 42))
	{
		exit_on("listen", __FILE__, __LINE__);
	}
	server->fds[s].type = FD_SERV;
	server->fds[s].read = server_accept;
}
