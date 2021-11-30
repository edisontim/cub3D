#include "cub3d.h"

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_d(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_cf_render_more(t_p *p, t_cf_v *cf, int y)
{
	int	x;

	x = 0;
	while (x < p->g_p.res[0])
	{
		cf->cell_x = (int)(cf->fl_x);
		cf->cell_y = (int)(cf->fl_y);
		cf->tx = (int)(p->fc_tex[0].img_w * \
				(cf->fl_x - cf->cell_x)) & (p->fc_tex[0].img_w - 1);
		cf->ty = (int)(p->fc_tex[1].img_h * \
				(cf->fl_y - cf->cell_y)) & (p->fc_tex[0].img_h - 1);
		cf->fl_x += cf->f_stp_x;
		cf->fl_y += cf->f_stp_y;
		cf->color = ft_tco(p->fc_tex[0], cf->tx, cf->ty);
		cf->color = (cf->color >> 1) & 8355711;
		ft_pixel_put(&p->b_img, x, y, cf->color);
		cf->color = ft_tco(p->fc_tex[1], cf->tx, cf->ty);
		cf->color = (cf->color >> 1) & 8355711;
		ft_pixel_put(&p->b_img, x, p->g_p.res[1] - y - 1, cf->color);
		x++;
	}
}

int	ft_cf_render(t_p *p, t_cf_v *cf)
{
	int	y;

	y = 0;
	while (y < p->g_p.res[1])
	{
		cf->ray_d_x0 = p->d_x - p->pl_x;
		cf->ray_d_y0 = p->d_y - p->pl_y;
		cf->ray_d_x1 = p->d_x + p->pl_x;
		cf->ray_d_y1 = p->d_y + p->pl_y;
		cf->p = y - p->g_p.res[1] / 2;
		cf->pos_z = 0.5 * p->g_p.res[1];
		cf->ro_dist = cf->pos_z / cf->p;
		cf->f_stp_x = cf->ro_dist * \
					  (cf->ray_d_x1 - cf->ray_d_x0) / p->g_p.res[0];
		cf->f_stp_y = cf->ro_dist * \
					  (cf->ray_d_y1 - cf->ray_d_y0) / p->g_p.res[0];
		cf->fl_x = p->pos_x + cf->ro_dist * cf->ray_d_x0;
		cf->fl_y = p->pos_y + cf->ro_dist * cf->ray_d_y0;
		ft_cf_render_more(p, cf, y);
		y++;
	}
	return (0);
}
