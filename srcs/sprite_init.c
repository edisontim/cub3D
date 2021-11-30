#include "cub3d.h"

void	ft_c_sprite(t_p *p, char **map, int argc)
{	
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				p->num_sprites++;
			}
			j++;
		}
		i++;
	}
	if (argc == 5)
		p->num_sprites++;
}

void	ft_a_sprite_init(t_p *p)
{	
	int	i;
	int	j;
	int	index;

	index = 0;
	i = 0;
	while (p->g_p.map[i] != NULL)
	{
		j = 0;
		while (p->g_p.map[i][j])
		{
			if (p->g_p.map[i][j] == '2')
			{
				p->sprite[index].x = i + 0.5;
				p->sprite[index].y = j + 0.5;
				index++;
			}
			j++;
		}
		i++;
	}
}

void	ft_sprite_u_init(t_p *p)
{
	p->sprite_order = malloc(sizeof(int) * p->num_sprites);
	p->sprite_distance = malloc(sizeof(double) * p->num_sprites);
	p->z_buffer = malloc(sizeof(double) * p->g_p.res[0]);
}

void	ft_sprite_init(t_p *p, int argc)
{
	ft_c_sprite(p, p->g_p.map, argc);
	p->sprite = malloc(p->num_sprites * sizeof(t_sprite));
	ft_a_sprite_init(p);
	ft_sprite_u_init(p);
}
