/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:37:24 by anestor           #+#    #+#             */
/*   Updated: 2018/03/03 23:37:45 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_rc	hor_len(t_wolf *data, double angle)
{
	t_xy	i;
	t_rc	ret;
	int		index;

	if (angle > 0 && angle < 180)
		i.y = (int)floor(data->player.y / CUBE) * (CUBE) - 1;
	else
		i.y = (int)floor(data->player.y / CUBE) * (CUBE) + CUBE;
	i.x = data->player.x + (data->player.y - i.y) / tan(RAD(angle));	
	if ((int)floor(i.y / CUBE) < 0 || (int)floor(i.y / CUBE) > data->map.y - 1
		|| (int)floor(i.x / CUBE) < 0 || (int)floor(i.x / CUBE) > data->map.x - 1)
	{
		ret.len = 999;
//		printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
//			(int)floor(i.x / (CUBE)), angle, 0, ret.len);
		return (ret);
	}
	index = data->map.arr[(int)floor(i.y / (CUBE))][(int)floor(i.x / (CUBE))];
	while (index == 0)
	{
		if (angle > 0 && angle < 180)
			i.y = i.y + -(CUBE);
		else
			i.y = i.y + (CUBE);
		i.x = i.x + (CUBE) / tan(RAD(angle));
		if ((int)floor(i.y / CUBE) < 0 || (int)floor(i.y / CUBE) > data->map.y - 1
			|| (int)floor(i.x / CUBE) < 0 || (int)floor(i.x / CUBE) > data->map.x - 1)
		{
			ret.len = 999;
//			printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
//				(int)floor(i.x / (CUBE)), angle, 0, ret.len);
			return (ret);
		}
		index = data->map.arr[(int)floor(i.y / (CUBE))][(int)floor(i.x / (CUBE))];
	}
	ret.col = data->map.col[index - 1];
	ret.len = sqrt(pow(data->player.x - i.x, 2) + pow(data->player.y - i.y, 2)); //cos
//	ret.len = ret.len * cos(RAD((angle - data->player.a)));
	printf("  y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
		(int)floor(i.x / (CUBE)), angle, ret.col, ret.len);
	return (ret);
}

t_rc	ver_len(t_wolf *data, double angle)
{
	t_xy	i;
	t_rc	ret;
	int		index;

	if (angle < 90 || angle > 270)
		i.x = (int)floor(data->player.x / CUBE) * (CUBE) + CUBE;
	else
		i.x = (int)floor(data->player.x / CUBE) * (CUBE) - 1;
	i.y = data->player.y + (data->player.x - i.x) * tan(RAD(angle));
	if ((int)floor(i.y / CUBE) < 0 || (int)floor(i.y / CUBE) > data->map.y - 1
		|| (int)floor(i.x / CUBE) < 0 || (int)floor(i.x / CUBE) > data->map.x - 1)
	{
		ret.len = 999;
//		printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
//			(int)floor(i.x / (CUBE)), angle, 0, ret.len);
		return (ret);
	}
	index = data->map.arr[(int)floor(i.y / (CUBE))][(int)floor(i.x / (CUBE))];		
	while (index == 0)
	{
		if (angle < 90 || angle > 270)
			i.x = i.x + (CUBE);
		else
			i.x = i.x + -(CUBE);
		i.y = i.y - (CUBE) * tan(RAD(angle));
		if ((int)floor(i.y / CUBE) < 0 || (int)floor(i.y / CUBE) > data->map.y - 1
			|| (int)floor(i.x / CUBE) < 0 || (int)floor(i.x / CUBE) > data->map.x - 1)
		{
			ret.len = 999;
//			printf("y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
//				(int)floor(i.x / (CUBE)), angle, 0, ret.len);
			return (ret);
		}
		index = data->map.arr[(int)floor(i.y / (CUBE))][(int)floor(i.x / (CUBE))];
	}
	ret.col = data->map.col[index - 1];
	ret.len = sqrt(pow(data->player.x - i.x, 2) + pow(data->player.y - i.y, 2)); //cos
//	ret.len = ret.len * cos(RAD((angle - data->player.a)));
	printf("v y: %d x: %d a: %f i: %d l: %f\n", (int)floor(i.y / (CUBE)),
			(int)floor(i.x / (CUBE)), angle, ret.col, ret.len);
	return (ret);
}

void	ray_casting(t_wolf *data)
{
	t_rc	slice[2];
	double 	angle;
	int		n;
	int		slice_h;

	n = 0;
	angle = fmod((data->player.a - (PP_ANGLE / 2)) + 360, 360);
	while (n != WIN_W)
	{
		slice[0] = hor_len(data, angle);
		slice[1] = ver_len(data, angle);
		if (slice[0].len < slice[1].len)
			ft_memcpy(&data->slice[n], &slice[0], sizeof(t_rc));
		else
			ft_memcpy(&data->slice[n], &slice[1], sizeof(t_rc));
		slice_h = CUBE / data->slice[n].len * data->pp_d;
		data->slice[n].start = (WIN_H - slice_h) / 2;
		data->slice[n].end = data->slice[n].start + slice_h;
		angle += (double)PP_ANGLE / WIN_W;
		angle = fmod(angle + 360, 360);
		printf("                      %f %d %f\n", angle, data->slice[n].col, data->slice[n].len);
		n++;
	}
}
