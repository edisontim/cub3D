/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <tedison@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:34:02 by tedison           #+#    #+#             */
/*   Updated: 2021/05/27 11:01:02 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	send_movement(t_p *p, int bypass)
{
	struct sockaddr_in	servaddr;
	static t_other		other = {-1, -1};

	ft_bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(p->multi.port_other);
	servaddr.sin_addr.s_addr = inet_addr(p->multi.address);
	if (!bypass && other.x_pos == p->pos_x && other.y_pos == p->pos_y)
		return (1);
	other.x_pos = p->pos_x;
	other.y_pos = p->pos_y;
	sendto(p->multi.socket_fd, &other, sizeof(t_other), 0, \
			(const struct sockaddr *)&servaddr, sizeof(servaddr));
	return (1);
}
