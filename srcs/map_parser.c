/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <tedison@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:31:05 by tedison           #+#    #+#             */
/*   Updated: 2021/06/02 14:50:37 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_empty(char *line)
{
	int	i;
	int	empty;

	empty = 1;
	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '\n' || line[i] == '\t'
				|| line[i] == '\r' || line[i] == '\f'
				|| line[i] == '\v'))
			empty = 0;
		i++;
	}
	return (empty);
}

int	get_params(t_p *p, char *path)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	line = NULL;
	ft_bzero((void *)&p->g_p, sizeof(t_params));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!loop_params(fd, &line, count, p))
		return (0);
	if (!content_twice(&p->g_p))
		return (0);
	if (map_valid_content(line))
	{
		if (!(get_map_array(path, fd, line, &p->g_p)))
			return (0);
	}
	free(line);
	return (1);
}

int	g_m_array_o(char *line, int fd, int to_malloc)
{
	while (1)
	{
		if (get_next_line(fd, &line) == 0)
		{
			if (map_valid_content(line))
				to_malloc++;
			free(line);
			break ;
		}
		if (ft_empty(line))
		{
			free(line);
			continue ;
		}
		if (map_valid_content(line) == 0)
		{
			free(line);
			return (0);
		}
		to_malloc++;
		free(line);
	}
	return (to_malloc);
}

int	g_m_array_t(t_params *g_p, char *line, int fd, int line_num)
{
	int	to_malloc;

	while (1)
	{
		if (get_next_line(fd, &line) == 0)
		{
			to_malloc = map_valid_content(line);
			if (to_malloc)
			{
				g_p->map[line_num] = ft_substr(line, 0, to_malloc);
				if (!g_p->map[line_num++])
					return (ft_error_map(g_p, 1, &line));
			}
			free(line);
			break ;
		}
		if (ft_empty(line))
			continue ;
		to_malloc = map_valid_content(line);
		if (to_malloc)
			g_p->map[line_num++] = ft_substr(line, 0, to_malloc);
		free(line);
		continue ;
	}
	return (line_num);
}

int	get_map_array(char *path, int fd, char *line, t_params *g_p)
{
	size_t	to_malloc;
	int		line_num;

	to_malloc = 1;
	line_num = 0;
	if (map_valid_content(line))
		to_malloc++;
	to_malloc = g_m_array_o(line, fd, to_malloc);
	if (to_malloc == 0)
		return (0);
	g_p->map = malloc(sizeof(*(g_p->map)) * (to_malloc + 1));
	if (!g_p->map)
		return (ft_error_map(g_p, 0, NULL));
	close(fd);
	fd = open(path, O_RDONLY);
	to_malloc = 0;
	line_num = g_m_array_t(g_p, line, fd, line_num);
	if (line_num == 0)
		return (0);
	g_p->map[line_num] = NULL;
	close(fd);
	return (1);
}
