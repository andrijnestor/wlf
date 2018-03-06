/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:13:30 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 12:27:55 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_hooks(int keycode, t_wolf *data)
{
	printf("k: %d\n", keycode);
	double	old;

	if (keycode == 124)
	{
		old = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-data->player.rot) - data->player.dir_y * sin(-data->player.rot);
		data->player.dir_y = old * sin(-data->player.rot) + data->player.dir_y * cos(-data->player.rot);
		old = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-data->player.rot) - data->player.plane_y * sin(-data->player.rot);
		data->player.plane_y = old * sin(-data->player.rot) + data->player.plane_y * cos(-data->player.rot);
//		data->player.a += 5;
	}
	if (keycode == 123)
	{
//		data->player.a -= 5;
	}
//	if (data->player.a < 0 || data->player.a > 360)
//		data->player.a = fmod(data->player.a + 360, 360);
	if (keycode == 126)
	{
		if (data->map.arr[(int)(data->player.x - data->player.dir_x * data->player.spd)][(int)data->player.y]
				== 0)
			data->player.x += data->player.dir_x * data->player.spd;
		if (data->map.arr[(int)(data->player.x)][(int)(data->player.y - data->player.dir_y * data->player.spd)]
				== 0)
			data->player.y += data->player.dir_y * data->player.spd;

	//	data->player.x = data->player.x + cos(data->player.a) * 10;
	//	data->player.y = data->player.y + sin(data->player.a) * 10;
	}
	if (keycode == 125)
	{
	//	data->player.x = data->player.x - cos(data->player.a) * 10;
	//	data->player.y = data->player.y - sin(data->player.a) * 10;
	}
	if (keycode == 53)
		wf_exit("Exit success");
//	mlx_destroy_image(data->mlx, data->walls.image);
	put_back_img(data);
	ray_casting(data);
	put_walls_img(data);
	return (0);
}
