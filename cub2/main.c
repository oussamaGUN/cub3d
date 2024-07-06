/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:01:39 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/07 00:05:01 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	CheckWalls(t_mlx data, char mv)
{
	int	x;
	int	y;

    return (1); /// need apdate
	x = (int )data.Player.x;
	y = (int )data.Player.y;
	if (mv == 'x')
		x -= (2 );
	else if (mv == 'X')
		x += (2 );
	else if (mv == 'y')
		y -= (2 );
	else if (mv == 'Y')
		y += (2 );
	if (data.map_info.map[x / SCALE][y / SCALE] != '0' && !IsPlayer(data.map_info.map[x / SCALE][y / SCALE]))
		return (0);
	return (1);
}

int key_hook(int keycode, void *data1)
{
    t_mlx *data;

    data = (t_mlx *)data1;
    if (keycode == 119 && CheckWalls(*data, 'x')) // up
    {
        data->Player.x += sin(data->map_info.direction) * PLAYERVET;
        data->Player.y += cos(data->map_info.direction) * PLAYERVET; 
    }
    else if (keycode == 115 && CheckWalls(*data, 'x')) // down
    {
        data->Player.x -= sin(data->map_info.direction) * PLAYERVET;
        data->Player.y -= cos(data->map_info.direction) * PLAYERVET;
    }
    else if (keycode == 100 && CheckWalls(*data, 'y')) // right
    {
        data->Player.x += sin(data->map_info.direction + M_PI / 2) * PLAYERVET;
        data->Player.y += cos(data->map_info.direction + M_PI / 2) * PLAYERVET;
    }
    else if (keycode == 97 && CheckWalls(*data, 'y')) // left
    {
        data->Player.x += sin(data->map_info.direction - M_PI / 2) * PLAYERVET;
        data->Player.y += cos(data->map_info.direction - M_PI / 2) * PLAYERVET;
    }
    else if (keycode == LEFT)
    {
        data->map_info.direction -= ANGLE;
    }
    else if (keycode == RIGHT)
    {
        data->map_info.direction += ANGLE;
    }

    // Normalize the direction within [0, 2 * M_PI]
    if (data->map_info.direction >= 2 * M_PI)
        data->map_info.direction -= 2 * M_PI;
    else if (data->map_info.direction < 0)
        data->map_info.direction += 2 * M_PI;

    mlx_clear_window(data->mlx, data->win);
    StandardMap(data);
    return 0;
}


int	main(int ac, char *av[])
{
	t_mlx	mlx_data;

	if (ac != 2 || ft_check_extension((char *)av[1], ".cub") == 0)
		return (printf("invalid argument\n"), 1);
	mlx_data.map_file.av = ft_strdup(av[1]);
	parsing(&mlx_data);
    initialize(&mlx_data);
	mlx_data.Player = GetPlayerPosition(mlx_data.map_info.map);
    StandardMap(&mlx_data);
    mlx_key_hook(mlx_data.win, key_hook, &mlx_data);
	mlx_loop(mlx_data.mlx);
	free(mlx_data.map_file.av);
	free_infos(&mlx_data);
	free(mlx_data.map_info.mapstr);
	free_split(mlx_data.map_info.map);
	return (0);
}

