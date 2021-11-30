#include "cub3d.h"

void	print_image(t_p *p, int tmp)
{
	int	color;
	int	x;
	int	y;

	write(p->fd, &tmp, 4);
	write(p->fd, &tmp, 4);
	write(p->fd, &tmp, 4);
	write(p->fd, &tmp, 4);
	y = p->g_p.res[1] - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < p->g_p.res[0])
		{
			color = ft_color(p->img, x, y);
			write(p->fd, &color, p->img.bbp / 8);
			x++;
		}
		y--;
	}
}

void	ft_image_to_bmp(t_p *p)
{
	int	tmp;

	p->fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, 0777);
	write(p->fd, "BM", 2);
	tmp = 40 + 14 + 4 * p->g_p.res[0] * \
		  p->g_p.res[1];
	write(p->fd, &tmp, 4);
	tmp = 0;
	write(p->fd, &tmp, 2);
	write(p->fd, &tmp, 2);
	tmp = 54;
	write(p->fd, &tmp, 4);
	tmp = 40;
	write(p->fd, &tmp, 4);
	write(p->fd, &p->g_p.res[0], 4);
	write(p->fd, &p->g_p.res[1], 4);
	tmp = 1;
	write(p->fd, &tmp, 2);
	write(p->fd, &p->img.bbp, 2);
	tmp = 0;
	write(p->fd, &tmp, 4);
	write(p->fd, &tmp, 4);
	print_image(p, tmp);
}
