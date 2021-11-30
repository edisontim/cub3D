#include "cub3d.h"

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_l + x * (data->bbp / 8));
	*(unsigned int *)dst = color;
}

void	ft_verline(t_p *p, int x, int y1, int y2)
{
	unsigned int	color;

	color = 0;
	if (y1 == 0)
		color = p->g_p.c_color;
	else
		color = p->g_p.f_color;
	while (y1 < y2)
	{
		ft_pixel_put(&p->img, x, y1, color);
		y1++;
	}
}

int	ft_trgb(int t, int r, int g, int b)
{
	int	a;

	if (t)
		return (t);
	a = t << 24;
	a += r << 16;
	a += g << 8;
	a += b;
	return (a);
}

uint32_t	ft_tco(t_texture t, int x, int y)
{
	char	*dst;

	dst = t.addr + (y * t.l_l + x * (t.bbp / 8));
	return (*(unsigned int *) dst);
}

int	ft_color(t_data data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.l_l + x * (data.bbp / 8));
	return (*(int *)dst);
}
