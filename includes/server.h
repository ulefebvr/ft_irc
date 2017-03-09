#ifndef SERVER_H
# define SERVER_H

# include <sys/time.h>
# include <sys/types.h>

# include <unistd.h>

#include "protocol.h"

# define BUF_SIZE		1024

typedef enum			e_type
{
	FD_FREE, FD_SERV, FD_CLIENT
}						t_type;

typedef struct			s_channel
{
	int					id;
	char				name[20];
	struct s_channel	*next;
}						t_channel;

typedef struct			s_fd
{
	t_type				type;
	char				auth;
	char				nickname[20];
	t_channel			*channel;
	void				(*read)();
	void				(*write)();
	char				buf_read[BUF_SIZE + 1];
	unsigned int		buffered;
	char				buf_write[BUF_SIZE + 1];
}						t_fd;

typedef struct			s_server
{
	int					port;
	int					max;
	int					maxfds;
	int					check;
	t_fd				*fds;
	fd_set				rfds;
	fd_set				wfds;
	t_channel			*channel_list;
}						t_server;

void		exit_on(char *str, char *file, int line);
void		initiate_limits(t_server *server);
void		server_getinfo(t_server *server, int ac, char **av);
void		server_launch(t_server *server);

void		server_accept(t_server *server, int s);

void		server_handle_io(t_server *server);

void		server_clean_fd(t_fd *fd);

void		server_loop(t_server *server);

void		client_read(t_server *server, int cs);

void		client_write(t_server *server, int cs);

void		server_client_nick(t_server *server, int cs, t_header *msg);
void		server_client_join(t_server *server, int cs, t_header *msg);
void		server_client_msg(t_server *server, int cs, t_header *msg);
void		server_client_leave(t_server *server, int cs, t_header *msg);
void		server_client_who(t_server *server, int cs, t_header *msg);

void		server_valid_respond(t_fd *fd, char *msg);
void		server_invalid_respond(t_fd *fd, char *msg);

#endif
