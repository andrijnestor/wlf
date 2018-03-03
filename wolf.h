/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:09:15 by anestor           #+#    #+#             */
/*   Updated: 2018/03/03 22:31:53 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h> // 
# define WIN_H 1000
# define WIN_W 1600
# define TOP_COLOR 0xAAAAFF
# define BOT_COLOR 0x222222
# define PP_ANGLE 60
# define CUBE 64
# define RAD(x) (x * M_PI / 180.0)
# define DEG(x) (x * 180.0 / M_PI)

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

typedef struct	s_rc
{
	int			col;
	double		len; //double?
	int			start;
	int			end;
}				t_rc;

typedef struct	s_plr
{
	int			x;
	int			y;
	double		a;
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
	int			*col;
	int			col_n;
	int			x;
	int			y;
}				t_map;

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	t_img		walls;
	t_img		back;
	t_map		map;
	t_plr		player;
	t_rc		slice[WIN_W];
	double		pp_a;
	int			pp_d;
}				t_wolf;

int				wf_exit(void *msg);

int				read_file(t_wolf *data, char *file);

void			ray_casting(t_wolf *data);

void			put_back_img(t_wolf *data);

void			put_walls_img(t_wolf *data);

int				key_hooks(int keycode, t_wolf *data);

#endif
