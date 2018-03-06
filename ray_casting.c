/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:37:24 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 21:55:44 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	calc_step_dist(t_wolf *data)
{
	if (data->cast.ray.x < 0)
	{
		data->cast.step.x = -1;
		data->cast.s_dist.x = (POX - MPX) * data->cast.d_dist.x;
	}
	else
	{
		data->cast.step.x = 1;
		data->cast.s_dist.x = (MPX + 1.0 - POX) * data->cast.d_dist.x;
	}
	if (data->cast.ray.y < 0)
	{
		data->cast.step.y = -1;
		data->cast.s_dist.y = (POY - MPY) * data->cast.d_dist.y;
	}
	else
	{
		data->cast.step.y = 1;
		data->cast.s_dist.y = (MPY + 1.0 - POY) * data->cast.d_dist.y;
	}
}

int		calc_side_and_mapxy(t_wolf *data)
{
	int		side;

	while (1)
	{
		if (data->cast.s_dist.x < data->cast.s_dist.y)
		{
			data->cast.s_dist.x += data->cast.d_dist.x;
			MPX += data->cast.step.x;
			side = 0;
		}
		else
		{
			data->cast.s_dist.y += data->cast.d_dist.y;
			MPY += data->cast.step.y;
			side = 1;
		}
		if (data->map.arr[MPY][MPX] > 0)
			break ;
	}
	return (side);
}

void	put_pixels(t_wolf *data, int y, int side, double dist, int line_h)
{
	double	wall_x;
	int		tex_x;
	int		x;

	if (side == 0)
		wall_x = POY + dist * data->cast.ray.y;
	else
		wall_x = POX + dist * data->cast.ray.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)TEX_W);
	if (side == 0 && data->cast.ray.x > 0)
		tex_x = TEX_W - tex_x - 1;
	if (side == 1 && data->cast.ray.y < 0)
		tex_x = TEX_W - tex_x - 1;
	x = 0;
	while (x != WIN_H)
	{
		if (data->slice[y].start <= x && data->slice[y].end > x)
		{
			int d = x * 256 - WIN_H * 128 + line_h * 128;
			int	tex_y = ((d * TEX_H) / line_h) / 256;
			int nn = (int)(data->map.arr[MPY][MPX] - 1);
			*(int *)(data->walls.addr + ((int)((y + x * WIN_W)) * sizeof(int)))
					= data->map.tex[nn][tex_x][tex_y];
		}
		else if (x <= WIN_H / 2)
			*(int *)(data->walls.addr + ((int)((y + x * WIN_W)) * sizeof(int)))
					= TOP_COLOR;
		else
			*(int *)(data->walls.addr + ((int)((y + x * WIN_W)) * sizeof(int)))
					= BOT_COLOR;
		x++;
	}
}

void	ray_casting(t_wolf *data)
{
	int		y;
	int		side;
	double	dist;
	int		line_h;

	y = -1;
	while (++y != WIN_W)
	{
		data->cast.ray.x = PDIR_X + PLANE_X * (2 * y / (double)WIN_W - 1);
		data->cast.ray.y = PDIR_Y + PLANE_Y * (2 * y / (double)WIN_W - 1);
		MPX = (int)POX;
		MPY = (int)POY;
		data->cast.d_dist.x = ABS((1 / data->cast.ray.x));
		data->cast.d_dist.y = ABS((1 / data->cast.ray.y));
		calc_step_dist(data);
		side = calc_side_and_mapxy(data);
		if (side == 0)
			dist = (MPX - POX + (1 - data->cast.step.x) / 2) / data->cast.ray.x;
		else
			dist = (MPY - POY + (1 - data->cast.step.y) / 2) / data->cast.ray.y;
		data->slice[y].start = -(int)(WIN_H / dist) / 2 + WIN_H / 2;
		data->slice[y].end = (int)(WIN_H / dist) / 2 + WIN_H / 2;
		line_h = (int)(WIN_H / dist);
//		data->slice[y].col = data->map.tex[data->map.arr[MPY][MPX] - 1][0][0];
//		if (side == 1)
//			data->slice[y].col = data->slice[y].col / 2;
		put_pixels(data, y, side, dist, line_h);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->walls.image, 0, 0);
}
