/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:31:10 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/05 16:42:25 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int IsPlayer(char c)
{
	if (c == 'N' || c == 'S' \
		|| c == 'E' || c == 'W')
		{
			return (1);
		}
	return (0);
}

t_cordonate GetPlayerPosition(char **map)
{
    int i;
    int j;
    t_cordonate pos;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (IsPlayer(map[i][j]))
            {
                pos.x = i * SCALE;
                pos.y = j * SCALE;
                return (pos);
            }
            j++;
        }
        i++;
    }
    return (pos);
}

void PlayerAdder(t_mlx *data)
{
    int x;
    int y;
    int r;
    int x0;
    int y0;

    r = 2;
    x0 = data->Player.x ;//+ SCALE / 2;
    y0 = data->Player.y ;//+ SCALE / 2;
    y = y0 - r;
    while ( y <= y0 + r)
    {
        x = x0 - r;
        while ( x <= x0 + r)
        {
            if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r)
                my_mlx_pixel_put(data, y, x, 0xE91111);
            x++;
        }
        y++;
    }
}

void    StandardMap(t_mlx *data)
{
    int         i;
    int         j;

    i = 0;

    while (i < data->map_info.height * SCALE)
    {
        j = 0;
        while (j < data->map_info.width * SCALE)
        {
            if (i % SCALE == 0 || j % SCALE == 0)
                 my_mlx_pixel_put(data, j, i, 0x767676);
            else if (data->map_info.map[i / SCALE][j / SCALE] == '1')//
                my_mlx_pixel_put(data, j, i, 0x00ff);
            else if ((i / SCALE) < data->map_info.height && (j / SCALE) < data->map_info.width &&
                 data->map_info.map[i / SCALE][j / SCALE] == '1')
                my_mlx_pixel_put(data, j, i, 0x00ff);
            else if (data->map_info.map[i / SCALE][j / SCALE] == '0' \
                    || IsPlayer(data->map_info.map[i / SCALE][j / SCALE]))
                my_mlx_pixel_put(data, j, i, 0xFFFFFF);
            else
                my_mlx_pixel_put(data, j , i , 0x0);
            j++;
        }
        i++;
    }
    PlayerAdder(data);
    
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
