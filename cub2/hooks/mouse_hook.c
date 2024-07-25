/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:32:32 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/25 17:33:03 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int close_win(void *data)
{
	t_mlx *mlx_data;
	mlx_data = (t_mlx *)data;
	mlx_destroy_window(mlx_data->mlx, mlx_data->win3d);
	exit(0);
}

void mouse_movement(t_mlx *data, int old_x , int old_y)
{
	data->map_info.maptype = 1;
	if (data->mouse.x > WIDTH - MINIW - 5 
		&& data->mouse.x < WIDTH && data->mouse.y > HEIGHT - MINIH - 5
		&& data->mouse.y < HEIGHT)
		data->map_info.maptype = 2;
	if (data->mouse.x < 0)
		data->map_info.direction -= (ANGLE / 5);
	else if (data->mouse.x > 1280)
		data->map_info.direction += (ANGLE / 5);
	if (data->mouse.x > old_x)
		data->map_info.direction += (ANGLE / 5);
	else if (data->mouse.x < old_x)
		data->map_info.direction -= (ANGLE / 5);
	if (data->mouse.y > old_y)
		data->jump -= ((ANGLE) * 20);
	else if (data->mouse.y < old_y)
		data->jump += ((ANGLE) * 20);
	if (data->jump > (ANGLE) * 2000)
		data->jump = (ANGLE) * 2000;
	else if (data->jump < - (ANGLE) * 2000)
		data->jump = - (ANGLE) * 2000;
}
int mouse_move(t_mlx *data)
{
	static int old_x = 0;
	static int old_y = 0;

	mlx_mouse_get_pos(data->mlx, data->win3d, &data->mouse.x, &data->mouse.y);
	mouse_movement(data, old_x, old_y);
	old_x = data->mouse.x;
	old_y = data->mouse.y;
	if (data->map_info.direction >= 2 * M_PI)
		data->map_info.direction -= 2 * M_PI;
	else if (data->map_info.direction < 0)
		data->map_info.direction += 2 * M_PI;
	mlx_clear_window(data->mlx, data->win3d);
	StandardMap(data);
	torch_animation(data);
	gate_animation(data);
	return (0);
}