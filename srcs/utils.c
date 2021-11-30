#include "cub3d.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int	ft_error(char *message)
{
	write(1, "Error\n", 6);
	ft_putstr(message);
	return (0);
}

void	ft_all_free(t_p *p)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (p->t_a[i].img != NULL)
			mlx_destroy_image(p->mlx, p->t_a[i].img);
		i++;
	}
	if (p->fc_tex[0].img && p->fc_tex[1].img)
	{
		free(p->g_p.f_texture);
		free(p->g_p.c_texture);
		mlx_destroy_image(p->mlx, p->fc_tex[0].img);
		mlx_destroy_image(p->mlx, p->fc_tex[1].img);
	}
	free_textures_sprites(p);
	mlx_destroy_image(p->mlx, p->img.img);
	mlx_destroy_window(p->mlx, p->mlx_win);
}

void	ft_exit(t_p *p, char *message)
{
	int	i;

	i = 0;
	if (message[0] != 0)
	{
		write(1, "Error\n", 6);
		ft_putstr(message);
	}
	ft_error_map(&p->g_p, 1, NULL);
	ft_all_free(p);
	exit(0);
}

int	red_exit(t_p *p)
{
	int	i;

	i = 0;
	write(1, "Pressed red cross\n", 18);
	ft_error_map(&p->g_p, 1, NULL);
	ft_all_free(p);
	exit(0);
}
