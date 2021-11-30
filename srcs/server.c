#include "cub3d.h"
#include <stdio.h>
#define MAXLINE 1024

int	socket_init(t_p *p)
{
	int					_true;
	struct sockaddr_in	servaddr;

	_true = 1;
	p->multi.socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (p->multi.socket_fd < 0)
		return (0);
	if (ioctl(p->multi.socket_fd, FIONBIO, &_true) == -1)
		return (0);
	ft_bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(p->multi.port);
	if (bind(p->multi.socket_fd, (const struct sockaddr *)&servaddr, \
			sizeof(servaddr)) < 0)
		return (0);
	return (1);
}

int	socket_frame(t_p *p)
{
	socklen_t			len;
	int					n;
	struct sockaddr_in	cliaddr;
	static t_other		o;
	static int			init = 0;

	memset(&cliaddr, 0, sizeof(cliaddr));
	len = sizeof(cliaddr);
	n = recvfrom(p->multi.socket_fd, &o, sizeof(t_other), 0, \
			(struct sockaddr *)&cliaddr, &len);
	if (n != -1)
	{
		if (!init)
		{
			send_movement(p, 1);
			init++;
		}
		p->multi.other = o;
		return (0);
	}
	return (0);
}
