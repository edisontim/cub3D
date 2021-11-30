#include "cub3d.h"

int	store_c_color(char *line, t_params *g_p)
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
		g_p->c_color = ft_trgb(0, color[0], color[1], color[2]);
		free(color);
		if (!ft_empty(&line[i]))
			return (0);
		g_p->c_c_check++;
		return (1);
	}
	else
		g_p->c_color = 0;
	free(color);
	return (0);
}

int	arg_more(char *line, t_params *g_p, int i, int *good)
{
	if (line[i] == 'S' && line[i + 1] != 'O')
		*good = store_sprite_p(&line[i + 1], g_p);
	if (line[i] == 'F' && line[i + 1] != 'T')
		*good = store_f_color(&line[i], g_p);
	if (line[i] == 'C' && line[i + 1] != 'T')
		*good = store_c_color(&line[i], g_p);
	if (line[i] == 'F' && line[i + 1] == 'T')
		*good = store_f_texture(&line[i + 1], g_p);
	if (line[i] == 'C' && line[i + 1] == 'T')
		*good = store_c_texture(&line[i + 1], g_p);
	return (1);
}

int	is_arg(char *line, t_params *g_p)
{
	int	i;
	int	good;

	good = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		good = store_res(&line[i], g_p);
	if (line[i] == 'N' && line[i + 1] == 'O')
		good = store_n_p(&line[i + 1], g_p);
	if (line[i] == 'S' && line[i + 1] == 'O')
		good = store_s_p(&line[i + 1], g_p);
	if (line[i] == 'W' && line[i + 1] == 'E')
		good = store_w_p(&line[i + 1], g_p);
	if (line[i] == 'E' && line[i + 1] == 'A')
		good = store_e_p(&line[i + 1], g_p);
	arg_more(line, g_p, i, &good);
	if (!good)
		return (0);
	return (1);
}
