#include "cub3d.h"

void	free_textures_sprites(t_p *p)
{
	free(p->g_p.n_p);
	free(p->g_p.s_p);
	free(p->g_p.w_p);
	free(p->g_p.e_p);
	free(p->g_p.sprite_p);
	free(p->sprite);
	free(p->sprite_order);
	free(p->sprite_distance);
	free(p->z_buffer);
}

int	loop_params(int fd, char **line, int count, t_p *p)
{	
	while (1)
	{
		if (count++ > 2000)
			return (0);
		get_next_line(fd, line);
		if (ft_empty(*line))
			continue ;
		if (map_valid_content(*line))
			break ;
		if (!is_arg(*line, &p->g_p))
			return (0);
		free(*line);
	}
	return (1);
}

int	content_twice(t_params *g_p)
{
	if (g_p->res_check != 1)
		return (0);
	if (g_p->no_p_check != 1)
		return (0);
	if (g_p->so_p_check != 1)
		return (0);
	if (g_p->we_p_check != 1)
		return (0);
	if (g_p->ea_p_check != 1)
		return (0);
	if (g_p->s_p_check != 1)
		return (0);
	if (g_p->f_c_check != 1)
		return (0);
	if (g_p->c_c_check != 1)
		return (0);
	return (1);
}
