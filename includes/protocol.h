#ifndef PROTOCOL_H
# define PROTOCOL_H

typedef enum	e_cmd
{
	CONNECT, RESPONSE, NICK, JOIN, QUIT, WHO, MSG, LEAVE
}				t_cmd;

typedef struct	s_header
{
	t_cmd		cmd;
	char		valid;
	char		private_msg;
	char		channel[20];
	char		from[20];
	char		to[20];
	char		msg[512];
}				t_header;

#endif