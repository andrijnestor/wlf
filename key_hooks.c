/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:13:30 by anestor           #+#    #+#             */
/*   Updated: 2018/03/07 16:19:48 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		loop_hook(t_wolf *data)
{
	if (data->key.right == 1)
		key_right(data);
	if (data->key.left == 1)
		key_left(data);
	if (data->key.down == 1)
		key_down(data);
	if (data->key.up == 1)
		key_up(data);
	ray_casting(data);
	mlx_string_put(data->mlx, data->win, 200, 200, 0xAAAAAA, "hi");
	return (0);
}

int		key_press_hooks(int keycode, t_wolf *data)
{
	printf("k: %d\n", keycode);
	if (keycode == 123)
		data->key.right = 1;
	if (keycode == 124)
		data->key.left = 1;
	if (keycode == 125)
		data->key.down = 1;
	if (keycode == 126)
		data->key.up = 1;
	if (keycode == 53)
		wf_exit("Exit success");
	return (0);
}

int		key_release_hooks(int keycode, t_wolf *data)
{
	if (keycode == 123)
		data->key.right = 0;
	if (keycode == 124)
		data->key.left = 0;
	if (keycode == 125)
		data->key.down = 0;
	if (keycode == 126)
		data->key.up = 0;
	return (0);
}

