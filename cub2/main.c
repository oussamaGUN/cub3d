/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:01:39 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/16 16:26:12 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	CheckWalls(t_mlx *data ,char **map, t_cordonate step, int keycode)
{
    long long x;
    long long y;

	x = (long long)(step.x / SCALE);
	y = (long long)(step.y / SCALE); 
    if (keycode != 119 && keycode != 115 && keycode != 100 && keycode != 97)
        return (0);
	if (map[y][x] != '0' && !IsPlayer(map[y][x]))
		return (0);

    if (((step.y + 1) / SCALE < data->map_info.height &&  map[(long long)((step.y + 1)/SCALE)][(long long)(step.x / SCALE)] == '1') ||\
         ((step.x + 1) / SCALE < data->map_info.width && map[(long long)((step.y)/SCALE)][(long long)((step.x + 1) / SCALE)] == '1'))
         {
             return (0);
         }
        
    return (1);
}

// int	CheckWalls(t_mlx data, char mv)
// {
// 	int	x;
// 	int	y;

//     return (1); /// need apdate
// 	x = (int )data.Player.x;
// 	y = (int )data.Player.y;
// 	if (mv == 'x')
// 		x -= (2 );
// 	else if (mv == 'X')
// 		x += (2 );
// 	else if (mv == 'y')
// 		y -= (2 );
// 	else if (mv == 'Y')
// 		y += (2 );
// 	if (data.map_info.map[x / SCALE][y / SCALE] != '0' && !IsPlayer(data.map_info.map[x / SCALE][y / SCALE]))
// 		return (0);
// 	return (1);
// }

int key_hook(int keycode, void *data1)
{
    t_mlx *data;
    t_cordonate step;

    data = (t_mlx *)data1;
    step.x = data->Player.x;
    step.y = data->Player.y;
    // data->jump = 0;
    if (keycode == ESC)
    {
        // free functions here
        exit(0);
    }
    else if (keycode == 119) // up
    {
        step.x += cos(data->map_info.direction) * PLAYERVET;
        step.y += sin(data->map_info.direction) * PLAYERVET;
    }
    else if (keycode == 115) // down
    {
        step.x -= cos(data->map_info.direction) * PLAYERVET;
        step.y -= sin(data->map_info.direction) * PLAYERVET;
    }
    else if (keycode == 100 ) // right
    {
        step.x += cos(data->map_info.direction + M_PI / 2) * PLAYERVET;
        step.y += sin(data->map_info.direction + M_PI / 2) * PLAYERVET;
    }
    else if (keycode == 97 ) // left
    {
        step.x += cos(data->map_info.direction - M_PI / 2) * PLAYERVET;
        step.y += sin(data->map_info.direction - M_PI / 2) * PLAYERVET;
    }
    else if (keycode == LEFT)
    {
        data->map_info.direction -= ANGLE;
    }
    else if (keycode == RIGHT)
    {
        data->map_info.direction += ANGLE;
    }
    if (CheckWalls(data, data->map_info.map, step, keycode))
    {
        data->Player.x = step.x;
        data->Player.y = step.y;
    }
    if (data->map_info.direction >= 2 * M_PI)
        data->map_info.direction -= 2 * M_PI;
    else if (data->map_info.direction < 0)
        data->map_info.direction += 2 * M_PI;

    //mlx_clear_window(data->mlx, data->win3d);
    //mlx_clear_window(data->mlx, data->win);
    StandardMap(data);
    return (0);
}

int mouse_move(t_mlx *data)
{
    static int old_x = 0;
    static int old_y = 0;
    int x;
    int y;

    mlx_mouse_get_pos(data->mlx, data->win3d, &x, &y);
    data->map_info.maptype = 1;
    if (x > WIDTH - MINIW - 5 && x < WIDTH && y > HEIGHT - MINIH - 5 && y < HEIGHT)
        data->map_info.maptype = 2;
    // for the ANGLE view
    if (x < 0)
        data->map_info.direction -= (ANGLE / 5);
    else if (x > 1280)
        data->map_info.direction += (ANGLE / 5);
    if (x > old_x)
        data->map_info.direction += (ANGLE / 5);
    else if (x < old_x)
        data->map_info.direction -= (ANGLE / 5);
    // for the jump view
    if (y > old_y)
        data->jump += (ANGLE / 5);
    else if (y < old_y)
        data->jump -= (ANGLE / 5);

    old_x = x;
    old_y = y;
    if (data->map_info.direction >= 2 * M_PI)
        data->map_info.direction -= 2 * M_PI;
    else if (data->map_info.direction < 0)
        data->map_info.direction += 2 * M_PI;
    mlx_clear_window(data->mlx, data->win3d);
    StandardMap(data);
    return (0);
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
    // StandardMap(&mlx_data);
    // mlx_key_hook(mlx_data.win, key_hook, &mlx_data);
    // mlx_hook(mlx_data.win,2, 1l>>0, key_hook, &mlx_data);
    mlx_hook(mlx_data.win3d,2, 1l>>0, key_hook, &mlx_data);
    mouse_move(&mlx_data);
    mlx_loop_hook(mlx_data.mlx, mouse_move, &mlx_data);
	mlx_loop(mlx_data.mlx);
	free(mlx_data.map_file.av);
	free_infos(&mlx_data);
	free(mlx_data.map_info.mapstr);
	free_split(mlx_data.map_info.map);
	return (0);
}

