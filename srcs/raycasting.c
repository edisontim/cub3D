#include "cub3d.h"

void	ft_dda(t_dda *dda, char **map)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->d_d_x;
			dda->map_x += dda->st_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->d_d_y;
			dda->map_y += dda->st_y;
			dda->side = 1;
		}
		if (map[dda->map_x][dda->map_y] == '1')
			dda->hit = 1;
	}
}

void	frame_one(t_p *p, t_dda *dda, t_f *f, int x)
{
	dda->hit = 0;
	f->camera_x = 2 * x / (double)(p->g_p.res[0]) - 1;
	f->ray_d_x = p->d_x + p->pl_x * f->camera_x;
	f->ray_d_y = p->d_y + p->pl_y * f->camera_x;
	dda->map_x = (int)p->pos_x;
	dda->map_y = (int)p->pos_y;
	if (f->ray_d_y == 0)
		dda->d_d_x = 0;
	else if (f->ray_d_x == 0)
		dda->d_d_x = 1;
	else
		dda->d_d_x = fabs(1 / f->ray_d_x);
	if (f->ray_d_x == 0)
		dda->d_d_y = 0;
	else if (dda->d_d_y == 0)
		dda->d_d_y = 1;
	else
		dda->d_d_y = fabs(1 / f->ray_d_y);
}

void	frame_two(t_p *p, t_dda *dda, t_f *f)
{
	if (f->ray_d_x < 0)
	{
		dda->st_x = -1;
		dda->side_dist_x = (p->pos_x - dda->map_x) * dda->d_d_x;
	}
	else
	{
		dda->st_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - p->pos_x) * dda->d_d_x;
	}
	if (f->ray_d_y < 0)
	{
		dda->st_y = -1;
		dda->side_dist_y = (p->pos_y - dda->map_y) * dda->d_d_y;
	}
	else
	{
		dda->st_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - p->pos_y) * dda->d_d_y;
	}
	ft_dda(dda, p->g_p.map);
	if (dda->side == 0)
		f->p_w_d = (dda->map_x - p->pos_x + (1 - dda->st_x) / 2) / f->ray_d_x;
	else
		f->p_w_d = (dda->map_y - p->pos_y + (1 - dda->st_y) / 2) / f->ray_d_y;
}

void	frame_start_ray(t_p *p, t_dda *dda, t_f *f)
{
	int	x;

	x = 0;
	while (x < p->g_p.res[0])
	{
		frame_one(p, dda, f, x);
		frame_two(p, dda, f);
		f->line_height = (int)(p->g_p.res[1] / f->p_w_d);
		f->dw_s = (-1) * f->line_height / 2 + p->g_p.res[1] / 2;
		if (f->dw_s < 0)
			f->dw_s = 0;
		f->dw_e = f->line_height / 2 + p->g_p.res[1] / 2;
		if (f->dw_e >= p->g_p.res[1])
			f->dw_e = p->g_p.res[1] - 1;
		ft_texture_render(p, f, *dda, x);
		p->z_buffer[x] = f->p_w_d;
		if (!p->g_p.f_texture && !p->g_p.c_texture)
		{
			ft_verline(p, x, 0, f->dw_s);
			ft_verline(p, x, f->dw_e, p->g_p.res[1]);
		}
		x++;
	}
}

int	frame(t_p *p)
{
	t_dda	dda;
	t_f		f;

	ft_bzero((void *)&dda, sizeof(dda));
	ft_bzero((void *)&f, sizeof(f));
	if (p->multi.address)
		socket_frame(p);
	printf("%f\n", p->multi.other.x_pos);
	ft_movements(p, p->g_p.map);
	if (p->multi.address)
		send_movement(p, 0);
	ft_rotate(p);
	f.p_w_d = 0;
	f.line_height = 0;
	p->screens++;
	if (p->g_p.f_texture && p->g_p.c_texture)
		ft_cf_render(p, &p->cf);
	frame_start_ray(p, &dda, &f);
	ft_sprites_render(p, &p->s_v);
	p->img = p->b_img;
	if (p->screens == 0)
		ft_image_to_bmp(p);
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->img.img, 0, 0);
	return (0);
}
