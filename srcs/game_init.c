#include "cub3d.h"
#include <stdio.h>
void	ft_orientation(char c, t_p *p, int i, int j)
{
	p->pos_x = i + 0.5;
	p->pos_y = j + 0.5;
	p->g_p.map[i][j] = '0';
	if (c == 'W')
	{
		p->d_y = -1;
		p->pl_x = -0.66;
	}
	if (c == 'E')
	{
		p->d_y = 1;
		p->pl_x = 0.66;
	}
	if (c == 'N')
	{
		p->d_x = -1;
		p->pl_y = 0.66;
	}
	if (c == 'S')
	{
		p->d_x = 1;
		p->pl_y = -0.66;
	}
}

int	get_p_pos(t_p *p)
{
	int	i;
	int	j;
	int	one_p;

	one_p = -1;
	i = -1;
	while (p->g_p.map[++i] != NULL)
	{
		j = -1;
		while (p->g_p.map[i][++j])
		{
			if (p->g_p.map[i][j] == 'N' || p->g_p.map[i][j] == 'W'
			|| p->g_p.map[i][j] == 'E' || p->g_p.map[i][j] == 'S')
			{
				if (++one_p != 0)
				{
					ft_error_map(&p->g_p, 1, NULL);
					return (ft_error("Multiple starting positions detected."));
				}
				ft_orientation(p->g_p.map[i][j], p, i, j);
			}
		}
	}
	return (1);
}

int	ft_surr(char **map, int i, int j)
{
	if (i == 0)
		return (0);
	if (j == 0)
		return (0);
	if (j > len(map[i - 1]))
		return (0);
	if (j > len(map[i + 1]))
		return (0);
	if ((map[i][j + 1] == '0' || map[i][j + 1] == '1' || map[i][j + 1] == '2')
			&& (map[i][j - 1] == '0' || map[i][j - 1] == '1'
				|| map[i][j - 1] == '2') && (map[i - 1][j] == '0'
				|| map[i - 1][j] == '1' || map[i - 1][j] == '2')
			&& (map[i + 1][j] == '0' || map[i + 1][j] == '1'
				|| map[i + 1][j] == '2'))
		return (1);
	return (0);
}

int	ft_check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == '2')
				if (!ft_surr(map, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_params(t_p *p)
{
	if (!ft_check_map(p->g_p.map))
	{
		ft_error_map(&p->g_p, 1, NULL);
		return (ft_error("Map entered as parameter is invalid."));
	}
	if (p->g_p.res[0] > 2560)
		p->g_p.res[0] = 2560;
	if (p->g_p.res[1] > 1440)
		p->g_p.res[1] = 1440;
	if (p->g_p.res[0] <= 0 || p->g_p.res[1] <= 0)
	{
		ft_error_map(&p->g_p, 1, NULL);
		return (ft_error("res entered is lower than 0."));
	}	
	return (1);
}
