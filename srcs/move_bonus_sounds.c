#include "cub3d.h"

void	key_s(t_p *p, char **map, double new_loc_x, double new_loc_y)
{
	if (map[(int)(p->pos_x - new_loc_x)][(int)p->pos_y] == '0')
		p->pos_x -= new_loc_x;
	else
		system("afplay ./outch.m4a& &>/dev/null -r 0.5");
	if (map[(int)p->pos_x][(int)(p->pos_y - new_loc_y)] == '0')
		p->pos_y -= new_loc_y;
	else
		system("afplay ./outch.m4a& &>/dev/null -r 0.5");
}

void	key_w(t_p *p, char **map, double new_loc_x, double new_loc_y)
{
	if (map[(int)(p->pos_x + new_loc_x)][(int)p->pos_y] == '0')
		p->pos_x += new_loc_x;
	else
		system("afplay ./outch.m4a& &>/dev/null -r 0.5");
	if (map[(int)p->pos_x][(int)(p->pos_y + new_loc_y)] == '0')
		p->pos_y += new_loc_y;
	else
		system("afplay ./outch.m4a& &>/dev/null -r 0.5");
}
