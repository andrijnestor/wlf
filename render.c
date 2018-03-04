/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:44:10 by anestor           #+#    #+#             */
/*   Updated: 2018/03/04 16:14:32 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_back_img(t_wolf *data)
{
	int		i;

	data->back.image = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->back.addr = mlx_get_data_addr(data->back.image, &data->back.bpp,
			&data->back.size_line, &data->back.endian);
	data->back.bpp /= 8;
	i = 0;
	while (i != WIN_H / 2 * WIN_W)
		*(int *)(data->back.addr + i++ * sizeof(int)) = TOP_COLOR;
	while (i != WIN_H * WIN_W)
		*(int *)(data->back.addr + i++ * sizeof(int)) = BOT_COLOR;
	mlx_put_image_to_window(data->mlx, data->win, data->back.image, 0, 0);
}

void	put_walls_img(t_wolf *data)
{
	t_xy	i;

	data->walls.image = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->walls.addr = mlx_get_data_addr(data->walls.image, &data->walls.bpp,
			&data->walls.size_line, &data->walls.endian);
	data->walls.bpp /= 8;
	i.x = 0;
	while (i.x != WIN_W)
	{
		i.y = 0;
		while (i.y != WIN_H)
		{
			if (data->slice[(int)(WIN_W - 1 - i.x)].start <= i.y && data->slice[(int)(WIN_W - 1 - i.x)].end >= i.y)
				*(int *)(data->walls.addr + ((int)((i.x + i.y * WIN_W)) * sizeof(int)))
					= data->slice[(int)(WIN_W - 1 - i.x)].col;
			else
				*(int *)(data->walls.addr + (((int)(i.x + i.y * WIN_W)) * sizeof(int)))
					= 255 << 24;
			i.y++;
		}
		i.x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->walls.image, 0, 0);
}
