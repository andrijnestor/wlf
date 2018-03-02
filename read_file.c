/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:26:58 by anestor           #+#    #+#             */
/*   Updated: 2018/03/02 19:35:58 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	read_colors(t_wolf *data, int fd)
{
	int		i;
	char	*line;

	if ((data->map.col = ft_memalloc(sizeof(int) * data->map.col_n)) == NULL)
		return (-1);
	i = 0;
	while (i != data->map.col_n)
	{
		if (get_next_line(fd, &line) < 0)
			return (-1);
		if (line == NULL)
			wf_exit("Map error");
	//	data->map.col[i] = ft_atoi_base(line, 16);
	//	data->map.col[i] = ft_atoi(line);
		data->map.col[i] = i;
		ft_memdel((void **)&line);
		i++;
	}
	return (0);
}

static int	read_map(t_wolf *data, int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**arr;

	i = 0;
	data->map.arr = ft_memalloc(sizeof(int *) * data->map.y);
	while (i != data->map.y)
	{
		get_next_line(fd, &line);
		(line == NULL) ? wf_exit("Map error") : (arr = ft_strsplit(line, ' '));
		ft_memdel((void **)&line);
		data->map.arr[i] = ft_memalloc(sizeof(int) * data->map.x);
		j = 0;
		while (j != data->map.x)
		{
			(arr[j] == NULL) ? wf_exit("Map error") : 0;
			data->map.arr[i][j] = ft_atoi(arr[j]);
			ft_memdel((void **)&arr[j++]);
		}
		ft_memdel((void **)&arr);
		ft_memdel((void **)&line);
		i++;
	}
	return (0);
}

static int	check_map(t_wolf *data)
{
	int		i;
	int		j;

	i = 0;
	while (i != data->map.y)
	{
		j = 0;
		while (j != data->map.x)
		{
			if (i == 0 || i == data->map.y - 1)
				if (data->map.arr[i][j] == 0)
					return (-1);
			if (j == 0 || j == data->map.x - 1)
				if (data->map.arr[i][j] == 0)
					return (-1);
			if (data->map.arr[i][j] < 0)
				return (-1);
			if (data->map.arr[i][j] > data->map.col_n)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int			read_file(t_wolf *data, char *file)
{
	int		fd;
	char	*line;
	char	**arr;

	if ((fd = open(file, O_RDWR)) < 0)
		wf_exit("No such file or directory");
	get_next_line(fd, &line);
	arr = ft_strsplit(line, ' ');
	ft_memdel((void **)&line);
	data->map.x = ft_atoi(arr[0]);
	ft_memdel((void **)&arr[0]);
	data->map.y = ft_atoi(arr[1]);
	ft_memdel((void **)&arr[1]);
	data->map.col_n = ft_atoi(arr[2]);
	ft_memdel((void **)&arr[2]);
	ft_memdel((void **)&arr);
	if (read_colors(data, fd) < 0)
		wf_exit("Out of memory");
	if (read_map(data, fd) < 0)
		wf_exit("Out of memory");
	close(fd);
	if (check_map(data) < 0)
		wf_exit("Map error");
	return (0);
}
