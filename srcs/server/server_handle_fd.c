#include "server.h"
#include "libft.h"

void			server_clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->auth = 0;
	if (fd->nickname != NULL)
	{
		ft_bzero(fd->nickname, 20);
	}
	fd->channel = NULL;
	fd->read = NULL;
	fd->buffered = 0;
	fd->write = NULL;
}