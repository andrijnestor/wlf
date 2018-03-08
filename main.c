/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:11:19 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 18:07:59 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		wf_exit(void *msg)
{
	ft_putendl((char *)msg);
	exit(1);
	return (0);
}

void	wolf_init(t_wolf *data)
{
	if ((data->mlx = mlx_init()) == NULL)
		wf_exit("MLX init problem");
	if ((data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "wolf3d"))
			== NULL)
		wf_exit("MLX init problem");
	if ((data->walls.image = mlx_new_image(data->mlx, WIN_W, WIN_H))
				== NULL)
		wf_exit("MLX init problem");
	data->walls.addr = mlx_get_data_addr(data->walls.image, &data->walls.bpp,
			&data->walls.size_line, &data->walls.endian);
	data->walls.bpp /= 8;
}

void	player_init(t_wolf *data)
{
	t_xy	i;

	i.y = WIN_H;
	i.x = WIN_W;
	if ((data->player.gun = F_TO_IMG("m_tex/gun.xpm", &i.x, &i.y)) == NULL)
		wf_exit("Texture error");
	if ((data->player.fire = F_TO_IMG("m_tex/fire_1.xpm", &i.x, &i.y)) == NULL)
		wf_exit("Texture error");
	data->player.dir_x = 1;
	data->player.dir_y = 1;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.66;
	data->player.y = -1;
	while (++data->player.y != data->map.y)
	{
		data->player.x = -1;
		while (++data->player.x != data->map.x)
			if (data->map.arr[(int)data->player.y][(int)data->player.x] == 0)
			{
				data->player.y += 0.5;
				data->player.x += 0.5;
				return ;
			}
	}
	wf_exit("No place for player");
}

int		main(int argc, char **argv)
{
	t_wolf	*data;

	if (argc != 2 && argc != 3)
		wf_exit("Usage: ./wolf3d [map] || ./wolf3d [map1] [map2]");
	if ((data = ft_memalloc(sizeof(t_wolf))) == NULL)
		wf_exit("Out of memory");
	wolf_init(data);
	menu_init(data);
	data->file = ft_memalloc(sizeof(char *) * (argc - 1));
	data->file[0] = argv[1];
	if (argc == 3)
	{
		data->file[1] = argv[2];
		data->maps = 1;
	}
	read_file(data, data->file[0]);
	player_init(data);
	mlx_hook(data->win, 2, 0, key_press_hooks, data);
	mlx_hook(data->win, 3, 0, key_release_hooks, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_hook(data->win, 17, 1L << 17, wf_exit, "Exit success");
	mlx_loop(data->mlx);
	clean_menu_and_mlx(data);
	return (0);
}
