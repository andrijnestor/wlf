/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:05:03 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 01:31:11 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	menu_init(t_wolf *data)
{
	t_xy	i;

	data->menu = ft_memalloc(sizeof(t_menu));
	i.y = WIN_H;
	i.x = WIN_W;
	data->menu->back.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/menu_back.xpm", &i.x, &i.y);
	i.y = 50;
	i.x = 200;
	data->menu->new_game.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/new_game.xpm", &i.x, &i.y);
	data->menu->resume.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/resume.xpm", &i.x, &i.y);
	data->menu->lvl1.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/lvl1.xpm", &i.x, &i.y);
	data->menu->lvl2.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/lvl2.xpm", &i.x, &i.y);
	data->menu->exit.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/exit.xpm", &i.x, &i.y);
	data->menu->point.image =
		mlx_xpm_file_to_image(data->mlx, "m_tex/point.xpm", &i.x, &i.y);
	data->menu->p_y = (WIN_H / 20) * 6;
	data->menu->menu_lvl = 0;
	data->maps = 1;
}

void	menu_render(t_wolf *data)
{
	int		i;

	mlx_put_image_to_window(data->mlx, data->win, data->menu->back.image, 0, 0);
	i = 0;
	if (data->menu->menu_lvl == 0)
	{
		PUT_IG(data->menu->new_game.image, (WIN_W / 12) * 5, (WIN_H / 20) * 6);
		PUT_IG(data->menu->exit.image, (WIN_W / 12) * 5, (WIN_H / 20) * 9);
		PUT_IG(data->menu->point.image, (WIN_W / 12) * 4, data->menu->p_y);
	}
	else if (data->menu->menu_lvl == 1)
	{
		PUT_IG(data->menu->resume.image, (WIN_W / 12) * 5, (WIN_H / 20) * 6);
		PUT_IG(data->menu->new_game.image, (WIN_W / 12) * 5, (WIN_H / 20) * 9);
		PUT_IG(data->menu->exit.image, (WIN_W / 12) * 5, (WIN_H / 20) * 12);
		PUT_IG(data->menu->point.image, (WIN_W / 12) * 4, data->menu->p_y);
	}
	else if (data->menu->menu_lvl == 2)
	{
		PUT_IG(data->menu->lvl1.image, (WIN_W / 12) * 5, (WIN_H / 20) * 6);
		PUT_IG(data->menu->lvl2.image, (WIN_W / 12) * 5, (WIN_H / 20) * 9);
		PUT_IG(data->menu->point.image, (WIN_W / 12) * 4, data->menu->p_y);

	}
}
