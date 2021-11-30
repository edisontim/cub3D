/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <tedison@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:34:04 by tedison           #+#    #+#             */
/*   Updated: 2021/05/27 14:54:57 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_press(int key, t_p *p)
{
	if (key == 13)
		p->keys.w = 1;
	if (key == 0)
		p->keys.a = 1;
	if (key == 1)
		p->keys.s = 1;
	if (key == 2)
		p->keys.d = 1;
	if (key == 123)
		p->keys.left = 1;
	if (key == 124)
		p->keys.right = 1;
	if (key == 53)
		ft_exit(p, "");
	return (0);
}

int	ft_release(int key, t_keys *keys)
{
	if (key == 13)
		keys->w = 0;
	if (key == 0)
		keys->a = 0;
	if (key == 1)
		keys->s = 0;
	if (key == 2)
		keys->d = 0;
	if (key == 123)
		keys->left = 0;
	if (key == 124)
		keys->right = 0;
	return (0);
}

void	ft_movements_more(t_p *p, char **map)
{
	double	new_loc_x;
	double	new_loc_y;
	double	new_strafe_x;
	double	new_strafe_y;

	new_loc_x = p->d_x * p->m_spd;
	new_loc_y = p->d_y * p->m_spd;
	new_strafe_x = p->pl_x * p->str_s;
	new_strafe_y = p->pl_y * p->str_s;
	if (p->keys.s)
		key_s(p, map, new_loc_x, new_loc_y);
	if (p->keys.a)
	{
		if (map[(int)(p->pos_x - new_strafe_x)][(int)p->pos_y] == '0')
			p->pos_x -= new_strafe_x;
		else
			system("afplay ./outch.m4a& &>/dev/null -r 0.5");
		if (map[(int)p->pos_x][(int)(p->pos_y - new_strafe_y)] == '0')
			p->pos_y -= new_strafe_y;
		else
			system("afplay ./outch.m4a& &>/dev/null -r 0.5");
	}
}

void	ft_movements(t_p *p, char **map)
{
	double	new_loc_x;
	double	new_loc_y;
	double	new_strafe_x;
	double	new_strafe_y;

	new_loc_x = p->d_x * p->m_spd;
	new_loc_y = p->d_y * p->m_spd;
	new_strafe_x = p->pl_x * p->str_s;
	new_strafe_y = p->pl_y * p->str_s;
	if (p->keys.w)
		key_w(p, map, new_loc_x, new_loc_y);
	if (p->keys.d)
	{
		if (map[(int)(p->pos_x + new_strafe_x)][(int)p->pos_y] == '0')
			p->pos_x += new_strafe_x;
		else
			system("afplay ./outch.m4a& &>/dev/null -r 0.5");
		if (map[(int)p->pos_x][(int)(p->pos_y + new_strafe_y)] == '0')
			p->pos_y += new_strafe_y;
		else
			system("afplay ./outch.m4a& &>/dev/null -r 0.5");
	}
	ft_movements_more(p, map);
}

void	ft_rotate(t_p *p)
{
	double	old_d_x;
	double	old_pl_x;

	old_d_x = p->d_x;
	old_pl_x = p->pl_x;
	if (p->keys.right)
	{
		p->d_x = p->d_x * cos(-p->r_spd) - p->d_y * sin(-p->r_spd);
		p->d_y = old_d_x * sin(-p->r_spd) + p->d_y * cos(-p->r_spd);
		p->pl_x = p->pl_x * cos(-p->r_spd) - p->pl_y * sin(-p->r_spd);
		p->pl_y = old_pl_x * sin(-p->r_spd) + p->pl_y * cos(-p->r_spd);
	}
	if (p->keys.left)
	{
		p->d_x = p->d_x * cos(p->r_spd) - p->d_y * sin(p->r_spd);
		p->d_y = old_d_x * sin(p->r_spd) + p->d_y * cos(p->r_spd);
		p->pl_x = p->pl_x * cos(p->r_spd) - p->pl_y * sin(p->r_spd);
		p->pl_y = old_pl_x * sin(p->r_spd) + p->pl_y * cos(p->r_spd);
	}
}
