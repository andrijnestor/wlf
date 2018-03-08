/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:56:19 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 18:08:11 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		loop_hook(t_wolf *data)
{
	if (data->key.space == 1)
	{
		data->player.fire_y = WIN_H - 330;
		data->key.space = !data->key.space;
	}
	else
		data->player.fire_y = WIN_H;
	if (data->key.right == 1)
		key_right(data);
	if (data->key.left == 1)
		key_left(data);
	if (data->key.down == 1)
		key_down(data);
	if (data->key.up == 1)
		key_up(data);
	if (data->menu->lvl == 1)
		ray_casting(data);
	else
		menu_render(data);
	return (0);
}

int		key_release_hooks(int keycode, t_wolf *data)
{
	if (keycode == 49)
		data->key.space = 0;
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

void	point_position_check(t_wolf *data)
{
	if (data->menu->p_y > (WIN_H / 20) * 9 && data->menu->menu_lvl != 1)
		data->menu->p_y = (WIN_H / 20) * 6;
	if (data->menu->p_y > (WIN_H / 20) * 12)
		data->menu->p_y = (WIN_H / 20) * 6;
	if (data->menu->p_y < (WIN_H / 20) * 6)
		data->menu->p_y = (WIN_H / 20) * 9;
}
