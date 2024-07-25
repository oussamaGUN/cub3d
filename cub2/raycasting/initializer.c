/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:49:07 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/24 23:40:56 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	initialize(t_mlx	*mlx)
{
	mlx->mouves.down = PLAYERVET * 30;
	mlx->mouves.up = PLAYERVET * 30;
	mlx->mouves.left = PLAYERVET * 30;
	mlx->mouves.right = PLAYERVET * 30;
	mlx->map_info.maptype = 1;
	mlx->win3d = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "RAYCASTING");
	mlx->img3d = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr3d = mlx_get_data_addr(mlx->img3d, &mlx->bits_per_pixel3d,
			&mlx->line_length3d, &mlx->endian3d);
}
