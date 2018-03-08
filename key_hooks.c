/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:13:30 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 18:01:53 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		menu_lvl_zero(t_wolf *data)
{
	if (data->menu->menu_lvl == 0)
	{
		if (data->menu->p_y == (WIN_H / 20) * 6)
		{
			if (data->maps == 1)
			{
				data->menu->menu_lvl = 2;
				return (1);
			}
			else
				data->menu->lvl = 1;
		}
		if (data->menu->p_y == (WIN_H / 20) * 9)
			wf_exit("Exit success");
	}
	return (0);
}

int		menu_lvl_one(t_wolf *data)
{
	if (data->menu->menu_lvl == 1)
	{
		if (data->menu->p_y == (WIN_H / 20) * 6)
			data->menu->lvl = 1;
		if (data->menu->p_y == (WIN_H / 20) * 9)
		{
			if (data->maps == 1)
			{
				data->menu->p_y = (WIN_H / 20) * 6;
				data->menu->menu_lvl = 2;
				return (1);
			}
			else
			{
				clean_map(data);
				read_file(data, data->file[0]);
				player_init(data);
				data->menu->lvl = 1;
			}
		}
		if (data->menu->p_y == (WIN_H / 20) * 12)
			wf_exit("Exit success");
	}
	return (0);
}

int		menu_lvl_three(t_wolf *data)
{
	if (data->menu->menu_lvl == 2)
	{
		if (data->menu->p_y == (WIN_H / 20) * 6)
		{
			clean_map(data);
			read_file(data, data->file[0]);
			player_init(data);
			data->menu->lvl = 1;
		}
		if (data->menu->p_y == (WIN_H / 20) * 9)
		{
			clean_map(data);
			read_file(data, data->file[1]);
			player_init(data);
			data->menu->lvl = 1;
		}
	}
	return (0);
}

void	esc_button(t_wolf *data)
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

int		key_press_hooks(int keycode, t_wolf *data)
{
	if (keycode == 49)
		data->key.space = 1;
	if (keycode == 123)
		(data->menu->lvl != 0) ? data->key.right = 1 : 0;
	if (keycode == 124)
		(data->menu->lvl != 0) ? data->key.left = 1 : 0;
	if (keycode == 125)
		(data->menu->lvl != 0) ? data->key.down = 1 :
					(data->menu->p_y += (WIN_H / 20) * 3);
	if (keycode == 126)
		(data->menu->lvl != 0) ? data->key.up = 1 :
					(data->menu->p_y -= (WIN_H / 20) * 3);
	point_position_check(data);
	if (keycode == 36)
		if (menu_lvl_zero(data) == 1 || menu_lvl_one(data) == 1 ||
				menu_lvl_three(data) == 1)
			return (0);
	if (keycode == 53)
		esc_button(data);
	return (0);
}
