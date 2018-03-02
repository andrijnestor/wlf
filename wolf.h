/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:09:15 by anestor           #+#    #+#             */
/*   Updated: 2018/03/02 21:48:00 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h> // 
# define WIN_H 200
# define WIN_W 320
# define PP_ANGLE 60
# define CUBE 64
# define RAD(x) (x * M_PI / 180.0)
# define DEG(x) (x * 180.0 / M_PI)
# define XA(a, b) (a <= 0) ? (-b) : b
# define YA(b, c) b / tan(RAD(c))

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

typedef struct	s_cl
{
	int			col;
	double		len; //double?
}				t_cl;

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
	t_img		img;
	t_map		map;
	t_plr		player;
	double		pp_a;
	int			pp_d;
}				t_wolf;

void			wf_exit(char *msg);

int				read_file(t_wolf *data, char *file);

#endif
