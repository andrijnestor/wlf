/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:13:30 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 19:15:50 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	key_left(t_wolf *data)
{
	double tmp;

	tmp = PDIR_X;
	PDIR_X = PDIR_X * cos(ROT_SPD) - PDIR_Y * sin(ROT_SPD);
	PDIR_Y = tmp * sin(ROT_SPD) + PDIR_Y * cos(ROT_SPD);
	tmp = PLANE_X;
	PLANE_X = PLANE_X * cos(ROT_SPD) - PLANE_Y * sin(ROT_SPD);
	PLANE_Y = tmp * sin(ROT_SPD) + PLANE_Y * cos(ROT_SPD);
}

static void	key_right(t_wolf *data)
{
	double tmp;

	tmp = PDIR_X;
	PDIR_X = PDIR_X * cos(-ROT_SPD) - PDIR_Y * sin(-ROT_SPD);
	PDIR_Y = tmp * sin(-ROT_SPD) + PDIR_Y * cos(-ROT_SPD);
	tmp = PLANE_X;
	PLANE_X = PLANE_X * cos(-ROT_SPD) - PLANE_Y * sin(-ROT_SPD);
	PLANE_Y = tmp * sin(-ROT_SPD) + PLANE_Y * cos(-ROT_SPD);
}

static void	key_up(t_wolf *data)
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

static void	key_down(t_wolf *data)
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

int			key_hooks(int keycode, t_wolf *data)
{
	printf("k: %d\n", keycode);
	if (keycode == 123)
		key_right(data);
	if (keycode == 124)
		key_left(data);
	if (keycode == 125)
		key_down(data);
	if (keycode == 126)
		key_up(data);
	if (keycode == 53)
		wf_exit("Exit success");
//	mlx_destroy_image(data->mlx, data->walls.image);
//	put_back_img(data);
	ray_casting(data);
//	put_walls_img(data);
	return (0);
}
