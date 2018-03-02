/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:11:19 by anestor           #+#    #+#             */
/*   Updated: 2018/03/02 21:47:59 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wf_exit(char *msg)
{
	ft_putendl(msg);
	exit(1);
}

void	wolf_init(t_wolf *data)
{
//	data->mlx = mlx_init();
//	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "wolf3d");
	data->player.x = 120;
	data->player.y = 120;
	data->player.a = 110;
	data->player.y = data->map.y / 2;
	data->pp_a = PP_ANGLE / WIN_W;
	data->pp_d = (WIN_W / 2) / tan(RAD(PP_ANGLE / 2));
}

t_cl	hor_len(t_wolf *data, double angle)
{
	t_xy	i;
	t_cl	ret;
	int		index;

	if (angle > 0 && angle < 180)
		i.y = floor(data->player.y / CUBE) * (CUBE) + CUBE;
	else
		i.y = floor(data->player.y / CUBE) * (CUBE) - 1;
//	printf("%d\n", i.y);
	i.x = data->player.x + (data->player.y - i.y) / tan(RAD(angle));
//	printf("e: %d %d\n", (int)floor(i.y / CUBE), (int)floor(i.x / CUBE));
		if ((int)floor(i.y / CUBE) < 0 || (int)floor(i.y / CUBE) > data->map.y - 1
			|| (int)floor(i.x / CUBE) < 0 || (int)floor(i.x / CUBE) > data->map.x - 1)
		{
			ret.col = 0;
			ret.len = 0;
			printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
				(int)floor(i.x / (CUBE)), angle, 0, ret.len);
			return (ret);
		}
	index = data->map.arr[(int)floor(i.y / (CUBE))][(int)floor(i.x / (CUBE))];
//	printf("hi\n");
	while (index == 0)
	{
//		i.x = i.x + (XA(data->player.a, CUBE));
//		i.y = i.y + (YA(CUBE, angle));
		if (angle > 0 && angle < 180)
			i.y = i.y + (CUBE);
		else
			i.y = i.y + -(CUBE);
		i.x = i.x + (CUBE) / tan(RAD(angle));
	//	printf("e: %d %d\n", (int)floor(i.y / CUBE), (int)floor(i.x / CUBE));
		if ((int)floor(i.y / CUBE) < 0 || (int)floor(i.y / CUBE) > data->map.y - 1
			|| (int)floor(i.x / CUBE) < 0 || (int)floor(i.x / CUBE) > data->map.x - 1)
		{
			ret.col = 0;
			ret.len = 0;
			printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
				(int)floor(i.x / (CUBE)), angle, 0, ret.len);
			return (ret);
		}
		index = data->map.arr[(int)floor(i.y / (CUBE))][(int)floor(i.x / (CUBE))];

	}
//	ret.col = data->map.col[index - 1];
	ret.col = index;
	ret.len = sqrt(pow(data->player.x - i.x, 2) + pow(data->player.y - i.y, 2)); //cos
	printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
			(int)floor(i.x / (CUBE)), angle, index, ret.len);
	return (ret);
}

void	ray_casting(t_wolf *data)
{
	t_cl	*slices;
	double 	angle;
	int		n;

	n = 0;
	slices = ft_memalloc(sizeof(t_cl) * WIN_W);
	angle = data->player.a - (PP_ANGLE / 2);
	while (n != WIN_W)
	{
		slices[n] = hor_len(data, angle);
		angle += (double)PP_ANGLE / WIN_W;

	//	printf("%f %d %f\n", angle, slices[n].col, slices[n].len);
		n++;
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
	ray_casting(data);
	printf("test: %d\n", data->map.col[1]);
	printf("test 2: %f\n", 160 / tan(RAD(30)));
//	mlx_loop(data->mlx);
	ft_memdel((void **)&data);
	return (0);
}
