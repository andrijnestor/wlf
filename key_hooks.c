/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:13:30 by anestor           #+#    #+#             */
/*   Updated: 2018/03/07 21:06:34 by anestor          ###   ########.fr       */
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
	if (data->menu->lvl == 1)
		ray_casting(data);
	else
		menu_render(data);
	mlx_string_put(data->mlx, data->win, 200, 200, 0xAAAAAA, "hi");
	return (0);
}

int		key_press_hooks(int keycode, t_wolf *data)
{
	printf("k: %d\n", keycode);
	if (keycode == 123)
		if (data->menu->lvl != 0)
			data->key.right = 1;
	if (keycode == 124)
		if (data->menu->lvl != 0)
			data->key.left = 1;
	if (keycode == 125)
	{
		if (data->menu->lvl != 0)
			data->key.down = 1;
		else
			data->menu->p_y += (WIN_H / 20) * 3;
	}
	if (keycode == 126)
	{
		if (data->menu->lvl != 0)
			data->key.up = 1;
		else
			data->menu->p_y -= (WIN_H / 20) * 3;
	}

	if (data->menu->p_y > (WIN_H / 20) * 9 && data->menu->menu_lvl != 1)
		data->menu->p_y = (WIN_H / 20) * 6;
	if (data->menu->p_y > (WIN_H / 20) * 12)
		data->menu->p_y = (WIN_H / 20) * 6;
	if (data->menu->p_y < (WIN_H / 20) * 6)
		data->menu->p_y = (WIN_H / 20) * 9;

	if (keycode == 36)
	{
		if (data->menu->menu_lvl == 0 && data->menu->p_y == (WIN_H / 20) * 6)
		{
			if (data->maps == 1)
				return (data->menu->menu_lvl = 2);
			else
				data->menu->lvl = 1;
		}
		if (data->menu->menu_lvl == 0 && data->menu->p_y == (WIN_H / 20) * 9)
			wf_exit("Exit success");
		if (data->menu->menu_lvl == 1 && data->menu->p_y == (WIN_H / 20) * 6)
			data->menu->lvl = 1;
		if (data->menu->menu_lvl == 1 && data->menu->p_y == (WIN_H / 20) * 9)
		{
			if (data->maps == 1)
			{
				data->menu->p_y = (WIN_H / 20) * 6;
				return (data->menu->menu_lvl = 2);
			}
			else
			{
				read_file(data, "test.map");
				player_init(data);
				data->menu->lvl = 1;
			}
		}
		if (data->menu->menu_lvl == 1 && data->menu->p_y == (WIN_H / 20) * 12)
			wf_exit("Exit success");
		if (data->menu->menu_lvl == 2 && data->menu->p_y == (WIN_H / 20) * 6)
		{
				read_file(data, "test.map");
				player_init(data);
				data->menu->lvl = 1;
		}
		if (data->menu->menu_lvl == 2 && data->menu->p_y == (WIN_H / 20) * 9)
		{
				read_file(data, "test5.map");
				player_init(data);
				data->menu->lvl = 1;
		}
	}
	if (keycode == 53)
	{
		if (data->menu->lvl == 0 && data->menu->menu_lvl != 2)
			wf_exit("Exit success");
		if (data->menu->lvl == 0 && data->menu->menu_lvl == 2)
			data->menu->menu_lvl = 0;
		else
		{
			data->menu->lvl = !data->menu->lvl;
			data->menu->menu_lvl = 1;
			data->menu->p_y = (WIN_H / 20) * 6;
		}
	}
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
