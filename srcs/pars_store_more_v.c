/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_store_more_v.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <tedison@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:14:34 by tedison           #+#    #+#             */
/*   Updated: 2021/06/02 15:00:52 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	store_f_texture(char *line, t_params *g_p)
{	
	int	i;
	int	start;

	i = 2;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->f_texture = ft_substr(line, start, i - start);
	return (1);
}

int	store_c_texture(char *line, t_params *g_p)
{	
	int	i;
	int	start;

	i = 2;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->c_texture = ft_substr(line, start, i - start);
	return (1);
}

int	store_sprite_p(char *line, t_params *g_p)
{
	int	i;
	int	start;

	i = 1;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->sprite_p = ft_substr(line, start, i - start);
	g_p->s_p_check++;
	return (1);
}

int	color_loop(char *line, int **color, int *i, int *good)
{
	int	iter;
	int	comma;

	iter = 0;
	while (iter < 3)
	{
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			(*color)[iter] = ft_atoi(&line[*i]);
			*good += 1;
		}
		while (line[*i] >= '0' && line[*i] <= '9')
			*i = *i + 1;
		comma = 0;
		if (iter++ == 2)
			break ;
		while (line[*i] == ' ' || line[*i] == ',')
			if (line[(*i)++] == ',')
				comma++;
		if (comma != 1)
			return (0);
	}
	return (*good);
}

int	store_f_color(char *line, t_params *g_p)
{
	int	i;
	int	good;
	int	*color;

	good = 0;
	i = 1;
	color = malloc(sizeof(int) * 3);
	while (line[i] == ' ')
		i++;
	good = color_loop(line, &color, &i, &good);
	if (good == 3 && color[0] >= 0 && color[0] <= 255
		&& color[1] >= 0 && color[1] <= 255
		&& color[2] >= 0 && color[2] <= 255)
	{
		g_p->f_color = ft_trgb(0, color[0], color[1], color[2]);
		free(color);
		if (!ft_empty(&line[i]))
			return (0);
		g_p->f_c_check++;
		return (1);
	}
	else
		g_p->f_color = 0;
	free(color);
	return (0);
}
