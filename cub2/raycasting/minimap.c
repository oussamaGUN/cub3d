/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:10:07 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/24 23:49:40 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	AddDirection(t_mlx *data, int W, int H)
{
	t_cordonate	Player;
	int			n;

	Player.x = WIDTH - W / 2 - 5;
	Player.y = HEIGHT - H / 2 - 5;
	n = 0;
	while (n < 20)
	{
		Player.x += cos(data->map_info.direction);
		Player.y += sin(data->map_info.direction);
		my_mlx_pixel_put(data, Player.x, Player.y, 0xFF);
		n++;
	}
}

int	is_in_range(t_cordonate Player, int maptype, int i, int j)
{
	int	W;
	int	H;

	if (maptype == 1)
	{
		W = MINIW;
		H = MINIH;
	}
	else
	{
		W = MINIW2;
		H = MINIH2;
	}
    return (i >= Player.y - H / 2 && i <= Player.y + H / 2 && \
         j >= Player.x - W / 2 && j <= Player.x + W / 2);
}

void	fill_WH(t_cordonate *WH, int maptype)
{
	if (maptype == 1)
	{
		WH->x = MINIW;
		WH->y = MINIH;
	}
	else
	{
		WH->x = MINIW2;
		WH->y = MINIH2;
	}
}

void	putColorToMini(t_mlx *data, int i, int j)
{
	t_cordonate	WH;
	int			x;
	int			y;

	fill_WH(&WH, data->map_info.maptype);
	x = j - (data->Player.x - WH.x / 2) + WIDTH - WH.x - 5;
	y = i - (data->Player.y - WH.y / 2) + HEIGHT - WH.y - 5;
	if (i % SCALE == 0 || j % SCALE == 0)
		my_mlx_pixel_put(data, x, y, GRAY);
	else if (i >= data->Player.y - 2 && i <= data->Player.y + 2 &&\
		j >= data->Player.x - 2 && j <= data->Player.x + 2)
		my_mlx_pixel_put(data, x, y, 0xEE1D1D);
	else if (data->map_info.map[i / SCALE][j / SCALE] == '1')//
		my_mlx_pixel_put(data, x, y, 0x00ff);
	else if ((i / SCALE) < data->map_info.height && (j / SCALE) < data->map_info.width &&
		data->map_info.map[i / SCALE][j / SCALE] == '1')
		my_mlx_pixel_put(data, x, y, 0x00ff);
	else if (data->map_info.map[i / SCALE][j / SCALE] == '0' \
			|| IsPlayer(data->map_info.map[i / SCALE][j / SCALE]))
		my_mlx_pixel_put(data, x, y, 0xFFFFFF);
	else if (data->map_info.map[i / SCALE][j / SCALE] == 'D')//
		my_mlx_pixel_put(data, x, y, 0x00FFFF);
	else
		my_mlx_pixel_put(data, x, y, 0x0);
}

void	DrowMiniMap(t_mlx *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_info.height * SCALE)
	{
		j = 0;
		while (j < data->map_info.width * SCALE)
		{
			if (is_in_range(data->Player, data->map_info.maptype, i, j))
				putColorToMini(data, i, j);
			j++;
		}
		i++;
	}
}
