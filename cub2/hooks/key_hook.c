/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:31:25 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/25 17:31:34 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void key_hook_movement(int keycode , t_mlx *data, t_cordonate *step)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win3d);
		exit(0);
	}
	else if (keycode == W_KEY)
	{
		step->x += cos(data->map_info.direction) * PLAYERVET;
		step->y += sin(data->map_info.direction) * PLAYERVET;
	}
	else if (keycode == S_KEY)
	{
		step->x -= cos(data->map_info.direction) * PLAYERVET;
		step->y -= sin(data->map_info.direction) * PLAYERVET;
	}
	else if (keycode == D_KEY)
	{
		step->x += cos(data->map_info.direction + M_PI / 2) * PLAYERVET;
		step->y += sin(data->map_info.direction + M_PI / 2) * PLAYERVET;
	}
	else if (keycode == A_KEY)
	{
		step->x += cos(data->map_info.direction - M_PI / 2) * PLAYERVET;
		step->y += sin(data->map_info.direction - M_PI / 2) * PLAYERVET;
	}
}
void key_hook_direcion(int keycode, t_mlx *data)
{
	if (keycode == LEFT)
		data->map_info.direction -= ANGLE;
	else if (keycode == RIGHT)
		data->map_info.direction += ANGLE;
}
int key_hook(int keycode, void *data1)
{
	t_mlx *data;
	t_cordonate step;

	data = (t_mlx *)data1;
	step.x = data->Player.x;
	step.y = data->Player.y;
	key_hook_movement(keycode, data, &step);
	key_hook_direcion(keycode, data);
	if (checkwalls(data, data->map_info.map, &step, keycode))
	{
		data->Player.x = step.x;
		data->Player.y = step.y;
	}
	if (data->map_info.direction >= 2 * M_PI)
		data->map_info.direction -= 2 * M_PI;
	else if (data->map_info.direction < 0)
		data->map_info.direction += 2 * M_PI;
	return (0);
}