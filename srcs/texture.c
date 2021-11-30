#include "cub3d.h"

void	ft_w_face(t_dda dda, t_f *f)
{
	if (f->ray_d_x < 0 && dda.side == 0)
		f->tex_num = 0;
	if (f->ray_d_x >= 0 && dda.side == 0)
		f->tex_num = 1;
	if (f->ray_d_y < 0 && dda.side == 1)
		f->tex_num = 2;
	if (f->ray_d_y >= 0 && dda.side == 1)
		f->tex_num = 3;
}

void	ft_texture_render_more(t_p *p, t_f *f, t_dda dda, int x)
{
	int			y;
	uint32_t	color;

	y = f->dw_s;
	while (y < f->dw_e)
	{
		f->tex_y = (int)f->tx_p & (p->t_a[f->tex_num].img_h - 1);
		f->tx_p += f->step;
		color = ft_tco(p->t_a[f->tex_num], f->tex_x, f->tex_y);
		if (dda.side == 0)
			color = (color >> 1) & 8355711;
		ft_pixel_put(&p->b_img, x, y, color);
		y++;
	}
}

int	ft_texture_render(t_p *p, t_f *f, t_dda dda, int x)
{
	ft_w_face(dda, f);
	if (dda.side == 0)
		f->wall_x = p->pos_y + f->p_w_d * f->ray_d_y;
	else
		f->wall_x = p->pos_x + f->p_w_d * f->ray_d_x;
	f->wall_x -= floor((f->wall_x));
	f->tex_x = (int)(f->wall_x * (double)(p->t_a[f->tex_num].img_w));
	if (dda.side == 0 && f->ray_d_x > 0)
		f->tex_x = p->t_a[f->tex_num].img_w - f->tex_x - 1;
	if (dda.side == 1 && f->ray_d_y < 0)
		f->tex_x = p->t_a[f->tex_num].img_w - f->tex_x - 1;
	f->step = 1.0 * p->t_a[f->tex_num].img_h / f->line_height;
	f->tx_p = (f->dw_s - p->g_p.res[1] / 2 + f->line_height / 2) \
			  * f->step;
	ft_texture_render_more(p, f, dda, x);
	return (0);
}
