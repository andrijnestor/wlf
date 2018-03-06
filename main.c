/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:11:19 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 20:09:31 by anestor          ###   ########.fr       */
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
//	data->mlx = mlx_init();
//	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "wolf3d");
	data->player.dir_x = 1;
	data->player.dir_y = 1;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.66;
	data->player.y = -1;
	data->walls.image = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->walls.addr = mlx_get_data_addr(data->walls.image, &data->walls.bpp,
			&data->walls.size_line, &data->walls.endian);
	data->walls.bpp /= 8;
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

void	print_map(t_wolf *data)
{
	int		i;
	int		j;

	i = 0;
	while (i != data->map.y)
	{
		j = 0;
		while (j != data->map.x)
		{
			printf("%d ", data->map.arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void		test_put_img(t_wolf *data)
{
	t_img	test;
	t_xy	i;

	test.image = mlx_new_image(data->mlx, TEX_W, TEX_H);
	test.addr = mlx_get_data_addr(test.image, &test.bpp,
			&test.size_line, &test.endian);
	test.bpp /= 8;
	i.y = -1;
	while (++i.y != TEX_H)
	{
		i.x = -1;
		while (++i.x != TEX_W)
		{
			*(int *)(test.addr + ((int)((i.y + i.x * TEX_W)) * sizeof(int))) =
				data->map.tex[1][i.y][i.x];
				//0x00AAAA;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, test.image, 300, 300);
}

int		main(int argc, char **argv)
{
	t_wolf	*data;

//	double g = 34.99;
//	printf("floor: %f ceil: %f round: %f\n", floor(g), ceil(g), round(g));
	if (argc != 2)
		wf_exit("Usage: ./wolf3d [map]");
	if ((data = ft_memalloc(sizeof(t_wolf))) == NULL)
		wf_exit("Out of memory");
	data->mlx = mlx_init(); //
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "wolf3d"); //

	read_file(data, argv[1]);
	wolf_init(data);
	print_map(data);
//	test_put_img(data);
	//ray_casting(data);
//	put_back_img(data);
//	put_walls_img(data);
	mlx_hook(data->win, 2, 5, key_hooks, data); 
	mlx_hook(data->win, 17, 1L << 17, wf_exit, "Exit success");
	mlx_loop(data->mlx);
	ft_memdel((void **)&data);
	return (0);
}
