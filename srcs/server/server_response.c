#include "server.h"
#include "libft.h"

void		server_valid_respond(t_fd *fd, char *msg)
{
	t_header	*header;

	header = (t_header *)fd->buf_write;
	ft_bzero(header, sizeof(t_header) + 1);
	header->cmd = RESPONSE;
	header->valid = 1;
	ft_strcpy(header->msg, msg);
}

void		server_invalid_respond(t_fd *fd, char *msg)
{
	t_header	*header;

	header = (t_header *)fd->buf_write;
	ft_bzero(header, sizeof(t_header) + 1);
	header->cmd = RESPONSE;
	header->valid = 0;
	ft_strcpy(header->msg, msg);
}
