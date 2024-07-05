/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:49:07 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/04 23:30:03 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	initialize(t_mlx	*mlx)
{
	mlx->mlx = mlx_init();
	printf("%d %d\n", mlx->map_info.width , mlx->map_info.height );
	mlx->win = mlx_new_window(mlx->mlx, mlx->map_info.width * SCALE, mlx->map_info.height * SCALE, "minirt");
	mlx->img = mlx_new_image(mlx->mlx, mlx->map_info.width * SCALE, mlx->map_info.height * SCALE);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	
	// mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "minirt");
	// mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	// mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
	// 			&mlx->line_length, &mlx->endian);
}
