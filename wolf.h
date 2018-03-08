/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:09:15 by anestor           #+#    #+#             */
/*   Updated: 2018/03/07 23:58:20 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h> // 
# define WIN_H 800
# define WIN_W 1200
# define TEX_H 64
# define TEX_W 64
# define TOP_COLOR 0x222222
# define BOT_COLOR 0x444444
# define ROT_SPD 0.04
# define SPD 0.065
//# define PP_ANGLE 60
//# define CUBE 64
//# define RAD(x) (x * M_PI / 180.0)
//# define DEG(x) (x * 180.0 / M_PI)
# define ABS(x) (x < 0) ? x * -1 : x
# define POX data->player.x
# define POY data->player.y
# define PDIR_X data->player.dir_x
# define PDIR_Y data->player.dir_y
# define RDIR_X data->cast.ray.x
# define RDIR_Y data->cast.ray.y
# define PLANE_X data->player.plane_x
# define PLANE_Y data->player.plane_y
# define MPX data->cast.map.x
# define MPY data->cast.map.y
# define W_DIST data->cast.w_dist
# define LINE_H data->cast.line_h
# define SIDE data->cast.side
# define WALL_X data->cast.wall_x
# define F_WALL_X data->cast.floor_w.x
# define F_WALL_Y data->cast.floor_w.y
# define PXL *(int *)(data->walls.addr + ((int)((y + x * WIN_W)) * sizeof(int)))
# define PUT_IG(x, y, z) mlx_put_image_to_window(data->mlx, data->win, x, y, z)

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

typedef struct	s_dxy
{
	double		x;
	double		y;
}				t_dxy;

typedef struct	s_rc
{
	int			col;
	int			start;
	int			end;
}				t_rc;

typedef struct	s_cast
{
	t_xy		map;
	t_xy		step;
	t_dxy		ray;
	t_dxy		d_dist;
	t_dxy		s_dist;
	double		w_dist;
	int			side;
	int			line_h;
	double		wall_x;
	t_dxy		floor_w;
//	double		dist_w;
	double		dist_plr;
//	double		dist_cur;
}				t_cast;

typedef struct	s_plr
{
	void		*gun;
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		rot;
	double		spd;
}				t_plr;

typedef struct	s_img
{
	void		*image;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_map
{
	int			**arr;
	int			***tex;
	int			**f_tex;
	int			**c_tex;
	int			tex_n;
	int			tex_x;
	int			x;
	int			y;
}				t_map;

typedef struct	s_key
{
	int			up;
	int			down;
	int			left;
	int			right;
}				t_key;

typedef struct s_menu
{
	int			lvl;
	int			menu_lvl;
	t_img		back;
	t_img		new_game;
	t_img		resume;
	t_img		lvl1;
	t_img		lvl2;
	t_img		exit;
	t_img		point;
	int			p_y;
}				t_menu;

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	t_img		walls;
	t_img		back;
	t_map		map;
	t_plr		player;
	t_cast		cast;
	t_rc		slice[WIN_W];
	t_key		key;
	t_menu		*menu;
	int			maps;
	void		**file;
}				t_wolf;

int				wf_exit(void *msg);

int				read_file(t_wolf *data, char *file);

void			ray_casting(t_wolf *data);
void			floor_casting(t_wolf *data, int y);
void			put_pixels(t_wolf *data, int y);

//void			put_back_img(t_wolf *data);

//void			put_walls_img(t_wolf *data);

void			menu_init(t_wolf *data);
void			menu_render(t_wolf *data);

void	player_init(t_wolf *data);

int				loop_hook(t_wolf *data);
int				key_press_hooks(int keycode, t_wolf *data);
int				key_release_hooks(int keycode, t_wolf *data);
void			key_left(t_wolf *data);
void			key_right(t_wolf *data);
void			key_down(t_wolf *data);
void			key_up(t_wolf *data);

#endif
