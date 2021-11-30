/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <timothyedison@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:02:57 by tedison           #+#    #+#             */
/*   Updated: 2021/11/30 17:35:54 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "srcs/gnl/get_next_line_bonus.h"
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/ioctl.h>
# include <string.h>
# include <stdio.h>

typedef struct s_keys{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}				t_keys;

typedef struct s_sprite{
	double	x;
	double	y;
}				t_sprite;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bbp;
	int		l_l;
	int		e;
}				t_data;

typedef struct s_texture {
	void	*img;
	char	*addr;
	int		bbp;
	int		l_l;
	int		e;
	int		img_w;
	int		img_h;
}				t_texture;

typedef struct s_params{
	int				res[2];
	char			*n_p;
	char			*s_p;
	char			*w_p;
	char			*e_p;
	char			*sprite_p;
	unsigned int	f_color;
	unsigned int	c_color;
	char			*f_texture;
	char			*c_texture;
	char			**map;
	int				valid;
	int				res_check;
	int				no_p_check;
	int				so_p_check;
	int				we_p_check;
	int				ea_p_check;
	int				s_p_check;
	int				f_c_check;
	int				c_c_check;
}			t_params;

typedef struct s_f{
	double	camera_x;
	double	ray_d_x;
	double	ray_d_y;
	double	p_w_d;
	int		line_height;
	int		dw_s;
	int		dw_e;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tx_p;
}			t_f;

typedef struct s_s_v{
	double			spr_x;
	double			spr_y;
	double			i_det;
	double			tr_x;
	double			tr_y;
	int				spr_s_x;
	int				s_h;
	int				dw_s_y;
	int				dw_e_y;
	int				s_w;
	int				dw_s_x;
	int				dw_e_x;
	int				tex_x;
	int				tex_y;
	uint32_t		color;
	int				stripe;
}				t_s_v;

typedef struct s_cf_v{
	float		ray_d_x0;
	float		ray_d_y0;
	float		ray_d_x1;
	float		ray_d_y1;
	int			p;
	float		pos_z;
	float		ro_dist;
	float		f_stp_x;
	float		f_stp_y;
	float		fl_x;
	float		fl_y;
	int			cell_x;
	int			cell_y;
	int			tx;
	int			ty;
	uint32_t	color;
}				t_cf_v;

typedef struct s_other{
	double	x_pos;
	double	y_pos;
}				t_other;

typedef struct s_multi{
	char	*address;
	int		socket_fd;
	int		port;
	int		port_other;
	t_other	other;
}				t_multi;

typedef struct s_p{
	double		pos_x;
	double		pos_y;
	double		d_x;
	double		d_y;
	double		pl_x;
	double		pl_y;
	double		m_spd;
	double		r_spd;
	double		str_s;
	t_keys		keys;
	char		**map;
	t_data		img;
	t_params	g_p;
	t_data		b_img;
	t_texture	t_a[4];
	void		*mlx;
	void		*mlx_win;
	int			num_sprites;
	t_sprite	*sprite;
	int			*sprite_order;
	double		*sprite_distance;
	double		*z_buffer;
	t_texture	s_texture;
	t_s_v		s_v;
	t_texture	fc_tex[2];
	t_cf_v		cf;
	t_multi		multi;
	int			size_x;
	int			size_y;
	int			screens;
	int			fd;
}				t_p;

typedef struct s_dda{
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		st_x;
	int		st_y;
	double	d_d_x;
	double	d_d_y;
}				t_dda;

int			get_map_array(char *path, int fd, char *line, \
		t_params *game_params);
int			g_m_array_t(t_params *g_p, char *line, int fd, int line_num);
int			g_m_array_o(char *line, int fd, int to_malloc);
int			get_params(t_p *p, char *path);
int			ft_empty(char *line);
int			ft_strcpy(char *dst, char *src);
char		*ft_strjoin(char const *s1, char const *s2);
int			get_next_line(int fd, char **line);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
int			ft_isprint(char c);
int			send_movement(t_p *p, int bypass);
int			socket_init(t_p *p);
int			socket_frame(t_p *p);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
void		ft_putstr(char *str);
int			ft_error(char *message);
int			ft_error_map(t_params *game_params, int free_all, char **line);
void		ft_exit(t_p *p, char *message);
int			red_exit(t_p *p);
void		ft_all_free(t_p *p);
void		ft_rotate(t_p *p);
void		ft_movements(t_p *p, char **map);
void		ft_movements_more(t_p *p, char **map);
int			ft_release(int key, t_keys *keys);
int			ft_press(int key, t_p *p);
void		ft_pixel_put(t_data *data, int x, int y, int color);
void		ft_verline(t_p *p, int x, int y1, int y2);
int			ft_trgb(int t, int r, int g, int b);
uint32_t	ft_tco(t_texture t, int x, int y);
int			ft_color(t_data data, int x, int y);
void		ft_w_face(t_dda dda, t_f *f);
void		ft_texture_render_more(t_p *p, t_f *f, t_dda dda, int x);
int			ft_texture_render(t_p *p, t_f *f, t_dda dda, int x);
int			ft_sprites_render(t_p *p, t_s_v *s_v);
void		ft_indiv_sprite_render(t_p *p, t_s_v *s_v, int d, int y);
void		ft_sprites_v(t_p *p, t_s_v *s_v, int i);
void		ft_s_array(t_p *p);
void		ft_sort_sprites(t_p *p);
void		ft_swap(int *a, int *b);
void		ft_swap_d(double *a, double *b);
int			ft_cf_render(t_p *p, t_cf_v *cf);
void		ft_cf_render_more(t_p *p, t_cf_v *cf, int y);
int			frame(t_p *p);
void		frame_start_ray(t_p *p, t_dda *dda, t_f *f);
void		frame_two(t_p *p, t_dda *dda, t_f *f);
void		frame_one(t_p *p, t_dda *dda, t_f *f, int x);
void		ft_dda(t_dda *dda, char **map);
void		print_image(t_p *p, int tmp);
void		ft_image_to_bmp(t_p *p);
void		ft_sprite_init(t_p *p, int argc);
void		ft_sprite_u_init(t_p *p);
void		ft_a_sprite_init(t_p *p);
void		ft_c_sprite(t_p *p, char **map, int argc);
int			check_params(t_p *p);
int			ft_check_map(char **map);
int			ft_surr(char **map, int i, int j);
int			get_p_pos(t_p *p);
void		ft_orientation(char c, t_p *p, int i, int j);
int			len(char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			map_valid_content(char *line);
size_t		ft_strlen_normal(const char *str);
int			store_e_p(char *line, t_params *g_p);
int			store_w_p(char *line, t_params *g_p);
int			store_s_p(char *line, t_params *g_p);
int			store_n_p(char *line, t_params *g_p);
int			store_res(char *l, t_params *g_p);
int			store_f_color(char *line, t_params *g_p);
int			color_loop(char *line, int **color, int *i, int *good);
int			store_sprite_p(char *line, t_params *g_p);
int			store_c_texture(char *line, t_params *g_p);
int			store_f_texture(char *line, t_params *g_p);
int			is_arg(char *line, t_params *g_p);
int			arg_more(char *line, t_params *g_p, int i, int *good);
int			store_c_color(char *line, t_params *g_p);
void		key_s(t_p *p, char **map, double new_loc_x, double new_loc_y);
void		key_w(t_p *p, char **map, double new_loc_x, double new_loc_y);
void		free_textures_sprites(t_p *p);
int			loop_params(int fd, char **line, int count, t_p *p);
int			content_twice(t_params *g_p);

#endif
