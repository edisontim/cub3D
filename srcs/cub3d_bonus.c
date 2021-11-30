#include "cub3d.h"

int	ft_texture_more(t_p *p)
{
	p->s_texture.img = mlx_xpm_file_to_image(p->mlx, p->g_p.sprite_p, \
			&p->s_texture.img_w, &p->s_texture.img_h);
	if (p->s_texture.img == NULL)
		return (0);
	p->s_texture.addr = mlx_get_data_addr(p->s_texture.img, &p->s_texture.bbp, \
			&p->s_texture.l_l, &p->s_texture.e);
	if (p->g_p.f_texture && p->g_p.c_texture)
	{
		p->fc_tex[0].img = mlx_xpm_file_to_image(p->mlx, p->g_p.f_texture, \
				&p->fc_tex[0].img_w, &p->fc_tex[0].img_h);
		p->fc_tex[0].addr = mlx_get_data_addr(p->fc_tex[0].img, &p->fc_tex[0].bbp, \
				&p->fc_tex[0].l_l, &p->fc_tex[0].e);
		p->fc_tex[1].img = mlx_xpm_file_to_image(p->mlx, p->g_p.c_texture, \
				&p->fc_tex[1].img_w, &p->fc_tex[1].img_h);
		p->fc_tex[1].addr = mlx_get_data_addr(p->fc_tex[1].img, &p->fc_tex[1].bbp, \
				&p->fc_tex[1].l_l, &p->fc_tex[1].e);
	}
	return (1);
}

int	ft_textures(t_p *p)
{
	p->t_a[0].img = mlx_xpm_file_to_image(p->mlx, p->g_p.n_p, \
			&p->t_a[0].img_w, &p->t_a[0].img_h);
	p->t_a[1].img = mlx_xpm_file_to_image(p->mlx, p->g_p.s_p, \
			&p->t_a[1].img_w, &p->t_a[1].img_h);
	p->t_a[2].img = mlx_xpm_file_to_image(p->mlx, p->g_p.w_p, \
			&p->t_a[2].img_w, &p->t_a[2].img_h);
	p->t_a[3].img = mlx_xpm_file_to_image(p->mlx, p->g_p.e_p, \
			&p->t_a[3].img_w, &p->t_a[3].img_h);
	if (p->t_a[0].img == NULL || p->t_a[1].img == NULL
		|| p->t_a[2].img == NULL || p->t_a[3].img == NULL)
		return (0);
	p->t_a[0].addr = mlx_get_data_addr(p->t_a[0].img, &p->t_a[0].bbp, \
			&p->t_a[0].l_l, &p->t_a[0].e);
	p->t_a[1].addr = mlx_get_data_addr(p->t_a[1].img, &p->t_a[1].bbp, \
			&p->t_a[1].l_l, &p->t_a[1].e);
	p->t_a[2].addr = mlx_get_data_addr(p->t_a[2].img, &p->t_a[2].bbp, \
			&p->t_a[2].l_l, &p->t_a[2].e);
	p->t_a[3].addr = mlx_get_data_addr(p->t_a[3].img, &p->t_a[3].bbp, \
			&p->t_a[3].l_l, &p->t_a[3].e);
	if (!ft_texture_more(p))
		return (0);
	return (1);
}

int	len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	cub3d(t_p *p, int argc, char *argv[])
{
	if (!get_params(p, argv[1]))
		return (ft_error(".cub file was not formatted in the right way."));
	if (!get_p_pos(p))
		return (0);
	if (!check_params(p))
		return (0);
	p->mlx = mlx_init();
	p->mlx_win = mlx_new_window(p->mlx, p->g_p.res[0], p->g_p.res[1], "Cub3D");
	p->img.img = mlx_new_image(p->mlx, p->g_p.res[0], p->g_p.res[1]);
	p->img.addr = mlx_get_data_addr(p->img.img, \
			&p->img.bbp, &p->img.l_l, &p->img.e);
	p->b_img.img = mlx_new_image(p->mlx, p->g_p.res[0], p->g_p.res[1]);
	p->b_img.addr = mlx_get_data_addr(p->b_img.img, &p->b_img.bbp, &p->b_img.l_l, \
			&p->b_img.e);
	ft_sprite_init(p, argc);
	if (!ft_textures(p))
		ft_exit(p, "Wrong texture path.");
	if (argc == 5)
		socket_init(p);
	mlx_loop_hook(p->mlx, frame, p);
	mlx_hook(p->mlx_win, 17, 1L << 17, red_exit, p);
	mlx_hook(p->mlx_win, 2, 1L << 0, ft_press, p);
	mlx_hook(p->mlx_win, 3, 1L << 1, ft_release, &p->keys);
	mlx_loop(p->mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_p	p;

	if (argc != 2 && argc != 3 && argc != 5)
		return (ft_error("Invalid number of arguments."));
	ft_bzero((void *)&p, sizeof(t_p));
	if (argc == 5)
	{
		p.multi.port = ft_atoi(argv[2]);
		p.multi.port_other = ft_atoi(argv[3]);
		p.multi.address = argv[4];
	}
	if (argc == 3)
	{
		if (len(argv[2]) == 6 && !ft_strncmp(argv[2], "--save", 6))
			p.screens = -1;
		else
			return (ft_error("Invalid argument."));
	}
	p.m_spd = 0.08;
	p.r_spd = 0.08;
	p.str_s = 0.06;
	return (cub3d(&p, argc, argv));
}
