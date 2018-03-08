/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:03:36 by anestor           #+#    #+#             */
/*   Updated: 2018/03/08 17:02:02 by anestor          ###   ########.fr       */
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
	if ((tmp.image = F_TO_IMG(filename, &i.x, &i.y)) == NULL)
		wf_exit("Texture error");
	tmp.addr = mlx_get_data_addr(tmp.image, &tmp.bpp, &tmp.size_line,
																&tmp.endian);
	tmp.bpp /= 8;
	img = ft_memalloc(sizeof(int *) * TEX_H);
	i.y = -1;
	while (++i.y != TEX_H)
	{
		img[i.y] = ft_memalloc(sizeof(int) * TEX_W);
		i.x = -1;
		while (++i.x != TEX_W)
		{
			img[i.y][i.x] =
				*(int *)(tmp.addr + ((int)(i.y + i.x * TEX_W)) * sizeof(int));
		}
	}
	mlx_destroy_image(data->mlx, tmp.image);
	return (img);
}

void		texture_make_and_set(t_wolf *data, char *line, int i)
{
	t_xy	p;
	int		**col;

	col = texture_array(line, data);
	p.y = -1;
	while (++p.y != TEX_W)
	{
		data->map.tex[i][p.y] = ft_memalloc(sizeof(int) * TEX_W);
		p.x = -1;
		while (++p.x != TEX_H)
			data->map.tex[i][p.y][p.x] = col[p.y][p.x];
		ft_memdel((void **)&col[p.y]);
	}
	ft_memdel((void **)&col);
}

void		color_make_and_set(t_wolf *data, char *line, int i)
{
	t_xy	p;

	p.y = -1;
	while (++p.y != TEX_W)
	{
		data->map.tex[i][p.y] = ft_memalloc(sizeof(int) * TEX_W);
		p.x = -1;
		while (++p.x != TEX_H)
			data->map.tex[i][p.y][p.x] = ft_atoi_base(line, 16);
	}
}

int			read_textures(t_wolf *data, int fd)
{
	int		i;
	char	*line;

	if ((data->map.tex = ft_memalloc(sizeof(int **) * data->map.tex_n)) == NULL)
		return (-1);
	i = -1;
	while (++i != data->map.tex_n)
	{
		if (get_next_line(fd, &line) < 0)
			return (-1);
		if (line == NULL)
			wf_exit("Map error");
		data->map.tex[i] = ft_memalloc(sizeof(int *) * TEX_H);
		if (ft_strstr(line, ".xpm"))
			texture_make_and_set(data, line, i);
		else
			color_make_and_set(data, line, i);
		ft_memdel((void **)&line);
	}
	data->map.f_tex = texture_array("textures/floor_1.xpm", data);
	data->map.c_tex = texture_array("textures/ceil_1.xpm", data);
	return (0);
}
