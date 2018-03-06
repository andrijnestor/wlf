/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:11:19 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 13:46:34 by anestor          ###   ########.fr       */
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
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "wolf3d");
	data->player.x = 2;
	data->player.y = 2;
	data->player.dir_x = 1;
	data->player.dir_y = 0.5;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
	data->player.rot = 0.1;
	data->player.spd = 0.1;
//	data->player.a = 0;
//	data->pp_a = PP_ANGLE / WIN_W;
//	data->pp_d = (WIN_W / 2) / tan(RAD(PP_ANGLE / 2));
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

int		main(int argc, char **argv)
{
	t_wolf	*data;

//	double g = 34.99;
//	printf("floor: %f ceil: %f round: %f\n", floor(g), ceil(g), round(g));
	if (argc != 2)
		wf_exit("Usage: ./wolf3d [map]");
	if ((data = ft_memalloc(sizeof(t_wolf))) == NULL)
		wf_exit("Out of memory");
	read_file(data, argv[1]);
	wolf_init(data);
	print_map(data);
	ray_casting(data);
	put_back_img(data);
	put_walls_img(data);
	printf("test: %d\n", data->map.col[1]);
	printf("test 2: %f\n", 160 / tan(RAD(30)));
	mlx_hook(data->win, 2, 5, key_hooks, data); 
	mlx_hook(data->win, 17, 1L << 17, wf_exit, "Exit success");
	mlx_loop(data->mlx);
	ft_memdel((void **)&data);
	return (0);
}
