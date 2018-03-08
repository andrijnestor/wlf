/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:37:24 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 18:07:52 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	calc_step_dist(t_wolf *data)
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

static int	calc_side_and_mapxy(t_wolf *data)
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

void		floor_casting(t_wolf *data, int y)
{
	if (SIDE == 0 && RDIR_X > 0)
	{
		F_WALL_Y = MPY + WALL_X;
		F_WALL_X = MPX;
	}
	else if (SIDE == 0 && RDIR_X < 0)
	{
		F_WALL_Y = MPY + WALL_X;
		F_WALL_X = MPX + 1.0;
	}
	else if (SIDE == 1 && RDIR_Y > 0)
	{
		F_WALL_Y = MPY;
		F_WALL_X = MPX + WALL_X;
	}
	else
	{
		F_WALL_Y = MPY + 1.0;
		F_WALL_X = MPX + WALL_X;
	}
	data->cast.dist_plr = 0.0;
	if (data->slice[y].end < 0)
		data->slice[y].end = WIN_H;
}

void		ray_casting(t_wolf *data)
{
	int		y;

	y = -1;
	while (++y != WIN_W)
	{
		RDIR_X = PDIR_X + PLANE_X * (2 * y / (double)WIN_W - 1);
		RDIR_Y = PDIR_Y + PLANE_Y * (2 * y / (double)WIN_W - 1);
		MPX = (int)POX;
		MPY = (int)POY;
		data->cast.d_dist.x = ABS((1 / RDIR_X));
		data->cast.d_dist.y = ABS((1 / RDIR_Y));
		calc_step_dist(data);
		SIDE = calc_side_and_mapxy(data);
		if (SIDE == 0)
			W_DIST = (MPX - POX + (1 - data->cast.step.x) / 2) / RDIR_X;
		else
			W_DIST = (MPY - POY + (1 - data->cast.step.y) / 2) / RDIR_Y;
		data->slice[y].start = -(int)(WIN_H / W_DIST) / 2 + WIN_H / 2;
		data->slice[y].end = (int)(WIN_H / W_DIST) / 2 + WIN_H / 2;
		LINE_H = (int)(WIN_H / W_DIST);
		put_pixels(data, y);
	}
	PUT_IG(data->walls.image, 0, 0);
	PUT_IG(data->player.fire, WIN_W / 2 - 50, data->player.fire_y);
	PUT_IG(data->player.gun, 0, 0);
}
