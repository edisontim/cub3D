#include "cub3d.h"

int	store_res(char *l, t_params *g_p)
{
	int	i;
	int	good;

	good = 0;
	i = 1;
	while (l[i] == ' ')
		i++;
	if ((l[i] >= '0' && l[i] <= '9') || l[i] == '-' || l[i] == '+')
	{
		g_p->res[0] = ft_atoi(&l[i]);
		good++;
	}
	while ((l[i] >= '0' && l[i] <= '9') || l[i] == '-' || l[i] == '+')
		i++;
	while (l[i] == ' ')
		i++;
	if ((l[i] >= '0' && l[i] <= '9') || l[i] == '-' || l[i] == '+')
	{
		g_p->res[1] = ft_atoi(&l[i]);
		good++;
	}
	g_p->res_check++;
	if (good == 2 && g_p->res[0] > 0 && g_p->res[1] > 0)
		return (1);
	return (0);
}

int	store_n_p(char *line, t_params *g_p)
{
	int	i;
	int	start;

	i = 1;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->n_p = ft_substr(line, start, i - start);
	g_p->no_p_check++;
	return (1);
}

int	store_s_p(char *line, t_params *g_p)
{
	int	i;
	int	start;

	i = 1;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->s_p = ft_substr(line, start, i - start);
	g_p->so_p_check++;
	return (1);
}

int	store_w_p(char *line, t_params *g_p)
{
	int	i;
	int	start;

	i = 1;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->w_p = ft_substr(line, start, i - start);
	g_p->we_p_check++;
	return (1);
}

int	store_e_p(char *line, t_params *g_p)
{
	int	i;
	int	start;

	i = 1;
	while (line[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(line[i]))
		i++;
	g_p->e_p = ft_substr(line, start, i - start);
	g_p->ea_p_check++;
	return (1);
}
