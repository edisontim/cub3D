#include "cub3d.h"

void	ft_sort_sprites(t_p *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->num_sprites - 1)
	{
		j = 0;
		while (j < p->num_sprites - i - 1)
		{
			if (p->sprite_distance[j] < p->sprite_distance[j + 1])
			{
				ft_swap_d(&p->sprite_distance[j], &p->sprite_distance[j + 1]);
				ft_swap(&p->sprite_order[j], &p->sprite_order[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	ft_s_array(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_sprites)
	{
		p->sprite_order[i] = i;
		p->sprite_distance[i] = ((p->pos_x - p->sprite[i].x) * (p->pos_x - p->sprite[i].x) \
				+ (p->pos_y - p->sprite[i].y) * (p->pos_y - p->sprite[i].y));
		i++;
	}
	ft_sort_sprites(p);
}

void	ft_sprites_v(t_p *p, t_s_v *s_v, int i)
{
	if (i == p->num_sprites - 1 && p->multi.address)
	{
		s_v->spr_x = p->multi.other.x_pos - p->pos_x;
		s_v->spr_y = p->multi.other.y_pos - p->pos_y;
	}
	else
	{
		s_v->spr_x = p->sprite[p->sprite_order[i]].x - p->pos_x;
		s_v->spr_y = p->sprite[p->sprite_order[i]].y - p->pos_y;
	}
	s_v->i_det = 1.0 / (p->pl_x * p->d_y - p->d_x * p->pl_y);
	s_v->tr_x = s_v->i_det * (p->d_y * s_v->spr_x - p->d_x * s_v->spr_y);
	s_v->tr_y = s_v->i_det * (-p->pl_y * s_v->spr_x + p->pl_x * s_v->spr_y);
	s_v->spr_s_x = (int)((p->g_p.res[0] / 2) * (1 + s_v->tr_x / s_v->tr_y));
	s_v->s_h = abs((int)(p->g_p.res[1] / s_v->tr_y));
	s_v->dw_s_y = -s_v->s_h / 2 + p->g_p.res[1] / 2;
	if (s_v->dw_s_y < 0)
		s_v->dw_s_y = 0;
	s_v->dw_e_y = s_v->s_h / 2 + p->g_p.res[1] / 2;
	if (s_v->dw_e_y >= p->g_p.res[1])
		s_v->dw_e_y = p->g_p.res[1] - 1;
	s_v->s_w = abs((int)(p->g_p.res[1] / s_v->tr_y));
	s_v->dw_s_x = -s_v->s_w / 2 + s_v->spr_s_x;
	if (s_v->dw_s_x < 0)
		s_v->dw_s_x = 0;
}

void	ft_indiv_sprite_render(t_p *p, t_s_v *s_v, int d, int y)
{
	s_v->dw_e_x = s_v->s_w / 2 + s_v->spr_s_x;
	if (s_v->dw_e_x >= p->g_p.res[0])
		s_v->dw_e_x = p->g_p.res[0] - 1;
	s_v->stripe = s_v->dw_s_x;
	while (s_v->stripe < s_v->dw_e_x)
	{
		s_v->tex_x = (int)(256 * (s_v->stripe - (-s_v->s_w / 2 + s_v->spr_s_x)) \
				* p->s_texture.img_w / s_v->s_w) / 256;
		if (s_v->tr_y > 0 && s_v->stripe > 0 && s_v->stripe < p->g_p.res[0]
			&& s_v->tr_y < p->z_buffer[s_v->stripe])
		{
			y = s_v->dw_s_y;
			while (y < s_v->dw_e_y)
			{
				d = (y) * 256 - p->g_p.res[1] * 128 + s_v->s_h * 128;
				s_v->tex_y = ((d * p->s_texture.img_h) / s_v->s_h) / 256;
				s_v->color = ft_tco(p->s_texture, s_v->tex_x, s_v->tex_y);
				if ((s_v->color & 0x00ffffff) != 0)
					ft_pixel_put(&p->b_img, s_v->stripe, y, s_v->color);
				y++;
			}
		}
		s_v->stripe++;
	}
}

int	ft_sprites_render(t_p *p, t_s_v *s_v)
{
	int	i;
	int	d;
	int	y;

	y = 0;
	d = 0;
	i = 0;
	ft_s_array(p);
	s_v->stripe = 0;
	while (i < p->num_sprites)
	{
		ft_sprites_v(p, s_v, i);
		ft_indiv_sprite_render(p, s_v, d, y);
		i++;
	}
	return (0);
}
