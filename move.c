/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:13:46 by anestor           #+#    #+#             */
/*   Updated: 2018/03/07 16:14:42 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	key_left(t_wolf *data)
{
	double tmp;

	tmp = PDIR_X;
	PDIR_X = PDIR_X * cos(ROT_SPD) - PDIR_Y * sin(ROT_SPD);
	PDIR_Y = tmp * sin(ROT_SPD) + PDIR_Y * cos(ROT_SPD);
	tmp = PLANE_X;
	PLANE_X = PLANE_X * cos(ROT_SPD) - PLANE_Y * sin(ROT_SPD);
	PLANE_Y = tmp * sin(ROT_SPD) + PLANE_Y * cos(ROT_SPD);
}

void	key_right(t_wolf *data)
{
	double tmp;

	tmp = PDIR_X;
	PDIR_X = PDIR_X * cos(-ROT_SPD) - PDIR_Y * sin(-ROT_SPD);
	PDIR_Y = tmp * sin(-ROT_SPD) + PDIR_Y * cos(-ROT_SPD);
	tmp = PLANE_X;
	PLANE_X = PLANE_X * cos(-ROT_SPD) - PLANE_Y * sin(-ROT_SPD);
	PLANE_Y = tmp * sin(-ROT_SPD) + PLANE_Y * cos(-ROT_SPD);
}

void	key_up(t_wolf *data)
{
	t_xy	i;

	i.x = POX;
	i.y = POY + PDIR_Y * SPD;
	if (i.y < data->map.y && i.y >= 0 && i.x < data->map.x && i.x >= 0)
		if (data->map.arr[i.y][i.x] == 0)
			POY += PDIR_Y * SPD;
	i.x = POX + PDIR_X * SPD;
	i.y = POY;
	if (i.y < data->map.y && i.y >= 0 && i.x < data->map.x && i.x >= 0)
		if (data->map.arr[i.y][i.x] == 0)
			POX += PDIR_X * SPD;
}

void	key_down(t_wolf *data)
{
	t_xy	i;

	i.x = POX;
	i.y = POY - PDIR_Y * SPD;
	if (i.y < data->map.y && i.y >= 0 && i.x < data->map.x && i.x >= 0)
		if (data->map.arr[i.y][i.x] == 0)
			POY -= PDIR_Y * SPD;
	i.x = POX - PDIR_X * SPD;
	i.y = POY;
	if (i.y < data->map.y && i.y >= 0 && i.x < data->map.x && i.x >= 0)
		if (data->map.arr[i.y][i.x] == 0)
			POX -= PDIR_X * SPD;

}
