#include "cub3d.h"

int	ft_error_map(t_params *g_p, int free_all, char **line)
{
	int	i;

	i = 0;
	if (free_all == 1)
	{
		while (g_p->map[i])
		{
			free(g_p->map[i]);
			i++;
		}
	}
	if (line)
		free(*line);
	free(g_p->map);
	return (0);
}

size_t	ft_strlen_normal(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	map_valid_content(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E'
		|| line[i] == ' ')
		i++;
	if ((line[i] == '\n' || line[i] == '\0') && i > 0)
		return (i);
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;
	size_t	start_cpy;

	if (!s)
		return (NULL);
	start_cpy = start;
	substr = NULL;
	i = 0;
	if (start < ft_strlen_normal(s))
	{
		while (s[start_cpy++] && i < len)
			i++;
	}
	substr = malloc(sizeof(*substr) * (i + 1));
	if (!substr)
		return (substr);
	i = 0;
	if (start < ft_strlen_normal(s))
		while (s[start] && i < len)
			substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
