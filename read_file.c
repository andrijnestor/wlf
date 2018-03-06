/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:26:58 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 20:08:56 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	**texture_array(char *filename, t_wolf *data)
{
	t_img	tmp;
	t_xy	i;
	int		**img;

	i.x = TEX_W;
	i.y = TEX_H;
	tmp.image = mlx_xpm_file_to_image(data->mlx, filename, &i.x, &i.y);
	mlx_put_image_to_window(data->mlx, data->win, tmp.image, 0, 0);
	tmp.addr = mlx_get_data_addr(tmp.image, &tmp.bpp, &tmp.size_line,
																&tmp.endian);
	tmp.bpp /= 8;
	img = ft_memalloc(sizeof(int *) * WIN_H);
	i.y = -1;
	while (++i.y != TEX_H)
	{
		img[i.y] = ft_memalloc(sizeof(int) * WIN_W);
		i.x = -1;
		while (++i.x != TEX_W)
		{
			img[i.y][i.x] =
				*(int *)(tmp.addr + ((int)(i.y + i.x * TEX_W)) * sizeof(int));
		}
	}
	return (img);
}

static int	read_textures(t_wolf *data, int fd)
{
	int		i;
	t_xy	p;
	char	*line;
	int		**col;

	if ((data->map.tex = ft_memalloc(sizeof(int **) * data->map.tex_n)) == NULL)
		return (-1);
	i = 0;
	while (i != data->map.tex_n)
	{
		if (get_next_line(fd, &line) < 0)
			return (-1);
		if (line == NULL)
			wf_exit("Map error");
		data->map.tex[i] = ft_memalloc(sizeof(int *) * TEX_H);
		if (ft_strstr(line, ".xpm"))
		{
			col = texture_array(line, data);
			p.y = -1;
			while (++p.y != TEX_W)
			{
				data->map.tex[i][p.y] = ft_memalloc(sizeof(int) * TEX_W);
				p.x = -1;
				while (++p.x != TEX_H)
					data->map.tex[i][p.y][p.x] = col[p.y][p.x];
			}
		}
		else
		{
			p.y = -1;
			while (++p.y != TEX_W)
			{
				data->map.tex[i][p.y] = ft_memalloc(sizeof(int) * TEX_W);
				p.x = -1;
				while (++p.x != TEX_H)
					data->map.tex[i][p.y][p.x] = ft_atoi_base(line, 16);
			}
		}
		//	data->map.tex[i] = ft_atoi_base(line, 16);
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
		if (line == NULL)
			wf_exit("Map error");
		arr = ft_strsplit(line, ' ');
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
			if (data->map.arr[i][j] > data->map.tex_n)
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
	data->map.tex_n = ft_atoi(arr[2]);
	ft_memdel((void **)&arr[2]);
	ft_memdel((void **)&arr);
	if (read_textures(data, fd) < 0)
		wf_exit("Out of memory");
	if (read_map(data, fd) < 0)
		wf_exit("Out of memory");
	close(fd);
	if (check_map(data) < 0)
		wf_exit("Map error");
	return (0);
}
