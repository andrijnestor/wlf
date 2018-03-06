/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:37:24 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 13:48:37 by anestor          ###   ########.fr       */
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

void	ray_casting(t_wolf *data)
{
	int		y;
	int		side;
	double	dist_to_wall;

	y = -1;
	while (++y != WIN_W)
	{
		data->cast.ray.x = PDIR_X + PLANE_X * (2 * y / (double)WIN_W - 1);
		data->cast.ray.y = PDIR_Y + PLANE_Y * (2 * y / (double)WIN_W - 1);
		MPX = (int)POX;
		MPY = (int)POY;
		data->cast.d_dist.x = ABS(1 / data->cast.ray.x);
		data->cast.d_dist.y = ABS(1 / data->cast.ray.y);
		calc_step_dist(data);
		side = calc_side_and_mapxy(data);
		if (side == 0)
			dist_to_wall = (MPX - POX + (1 - data->cast.step.x) / 2) / data->cast.ray.x;
		else
			dist_to_wall = (MPY - POY + (1 - data->cast.step.y) / 2) / data->cast.ray.y;
		data->slice[y].start = -(int)(WIN_H / dist_to_wall) / 2 + WIN_H / 2; // if <0
		data->slice[y].end = (int)(WIN_H / dist_to_wall) / 2 + WIN_H / 2; // if > WIN_W
		data->slice[y].col = data->map.col[data->map.arr[MPY][MPX] - 1];
		if (side == 1)
			data->slice[y].col = data->slice[y].col / 2;
	}
}
