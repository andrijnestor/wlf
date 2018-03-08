/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:11:17 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 17:17:10 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	clean_menu_and_mlx(t_wolf *data)
{
	mlx_destroy_image(data->mlx, data->menu->back);
	mlx_destroy_image(data->mlx, data->menu->new_game);
	mlx_destroy_image(data->mlx, data->menu->resume);
	mlx_destroy_image(data->mlx, data->menu->lvl1);
	mlx_destroy_image(data->mlx, data->menu->lvl2);
	mlx_destroy_image(data->mlx, data->menu->exit);
	mlx_destroy_image(data->mlx, data->menu->point);
	ft_memdel((void **)&data->menu);
	mlx_destroy_window(data->mlx, data->win);
	ft_memdel((void **)&data->file);
	ft_memdel((void **)&data);
}

void	clean_map(t_wolf *data)
{
	t_xy	i;

	i.y = -1;
	while (++i.y != data->map.y)
		ft_memdel((void **)&data->map.arr[i.y]);
	ft_memdel((void **)&data->map.arr);
	i.y = -1;
	while (++i.y != data->map.tex_n)
	{
		i.x = -1;
		while (++i.x != TEX_W)
			ft_memdel((void **)&data->map.tex[i.y][i.x]);
		ft_memdel((void **)&data->map.tex[i.y]);
	}
	i.x = -1;
	while (++i.x != TEX_W)
	{
		ft_memdel((void **)&data->map.f_tex[i.x]);
		ft_memdel((void **)&data->map.c_tex[i.x]);
	}
	ft_memdel((void **)&data->map.f_tex);
	ft_memdel((void **)&data->map.c_tex);
	ft_memdel((void **)&data->map.tex);
	mlx_destroy_image(data->mlx, data->player.gun);
}
