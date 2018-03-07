/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:19:48 by anestor           #+#    #+#             */
/*   Updated: 2018/03/07 18:24:23 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	put_floor_top_pxl(t_wolf *data, int y, int x, double weight)
{
	double	dist_cur;
	int		floor_t_x;
	int		floor_t_y;
	double	cur_floor_x;
	double	cur_floor_y;

	dist_cur = WIN_H / (2.0 * x - WIN_H);
	weight = (dist_cur - data->cast.dist_plr) /
		(W_DIST - data->cast.dist_plr);
	cur_floor_x = weight * F_WALL_X + (1.0 - weight) * POX;
	cur_floor_y = weight * F_WALL_Y + (1.0 - weight) * POY;
	floor_t_x = (int)(cur_floor_x * TEX_W) % TEX_W;
	floor_t_y = (int)(cur_floor_y * TEX_H) % TEX_H;
	PXL = data->map.tex[0][floor_t_x][floor_t_y];
	PXL = (PXL >> 1) & 8355711;
	*(int *)(data->walls.addr + ((int)((y + ((WIN_H - x) *
		WIN_W))) * sizeof(int))) = data->map.tex[1][floor_t_y][floor_t_x];
}

static void	put_wall_pxl(t_wolf *data, int y, int x, int tex_x)
{
	int		k;
	int		n;
	int		tex_y;

	n = (int)(data->map.arr[MPY][MPX] - 1);
	k = x * 256 - WIN_H * 128 + LINE_H * 128;
	tex_y = ((k * TEX_H) / LINE_H) / 256;
	PXL = data->map.tex[n][tex_x][tex_y];
	if (SIDE == 1)
		PXL = (PXL >> 1) & 8355711;
}

void		put_pixels(t_wolf *data, int y)
{
	int		tex_x;
	int		x;

	if (SIDE == 0)
		WALL_X = POY + W_DIST * data->cast.ray.y;
	else
		WALL_X = POX + W_DIST * data->cast.ray.x;
	WALL_X -= floor((WALL_X));
	tex_x = (int)(WALL_X * (double)TEX_W);
	if (SIDE == 0 && data->cast.ray.x > 0)
		tex_x = TEX_W - tex_x - 1;
	if (SIDE == 1 && data->cast.ray.y < 0)
		tex_x = TEX_W - tex_x - 1;
	x = 0;
	floor_casting(data, y);
	while (x != WIN_H)
	{
		if (data->slice[y].start <= x && data->slice[y].end > x)
			put_wall_pxl(data, y, x, tex_x);
		else if (data->slice[y].end < x)
			put_floor_top_pxl(data, y, x, 0);
		x++;
	}
}
