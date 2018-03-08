/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:09:15 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 17:58:10 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft.h"
# include <math.h>
# include <mlx.h>
# define WIN_H 800
# define WIN_W 1200
# define TEX_H 64
# define TEX_W 64
# define ROT_SPD 0.04
# define SPD 0.065
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
# define F_TO_IMG(x, y, z) mlx_xpm_file_to_image(data->mlx, x, y, z)

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
	double		dist_plr;
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
	void		*fire;
	int			fire_y;
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
	int			space;
}				t_key;

typedef struct	s_menu
{
	int			lvl;
	int			menu_lvl;
	void		*back;
	void		*new_game;
	void		*resume;
	void		*lvl1;
	void		*lvl2;
	void		*exit;
	void		*point;
	int			p_y;
}				t_menu;

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	t_img		walls;
	t_map		map;
	t_plr		player;
	t_cast		cast;
	t_rc		slice[WIN_W];
	t_key		key;
	t_menu		*menu;
	int			maps;
	char		**file;
}				t_wolf;

/*
** exit
*/

int				wf_exit(void *msg);

/*
** reading map and textures
*/

int				read_file(t_wolf *data, char *file);
int				read_textures(t_wolf *data, int fd);

/*
** rendering
*/

void			ray_casting(t_wolf *data);
void			floor_casting(t_wolf *data, int y);
void			put_pixels(t_wolf *data, int y);
void			menu_render(t_wolf *data);

/*
** init settings
*/

void			menu_init(t_wolf *data);
void			player_init(t_wolf *data);

/*
** keys and hooks
*/

int				loop_hook(t_wolf *data);
int				key_press_hooks(int keycode, t_wolf *data);
int				key_release_hooks(int keycode, t_wolf *data);
void			key_left(t_wolf *data);
void			key_right(t_wolf *data);
void			key_down(t_wolf *data);
void			key_up(t_wolf *data);
void			point_position_check(t_wolf *data);

/*
** cleaning
*/

void			clean_menu_and_mlx(t_wolf *data);
void			clean_map(t_wolf *data);

#endif
