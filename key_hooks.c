/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:13:30 by anestor           #+#    #+#             */
/*   Updated: 2018/03/03 22:43:19 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_hooks(int keycode, t_wolf *data)
{
	if (keycode == 123)
		data->player.a -= 5;
	if (keycode == 124)
		data->player.a += 5;
	if (keycode == 53)
		wf_exit("Exit success");
	printf("k: %d\n", keycode);
//	mlx_destroy_image(data->mlx, data->walls.image);
	put_back_img(data);
	ray_casting(data);
	put_walls_img(data);
	return (0);
}
