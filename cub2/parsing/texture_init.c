/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:13:53 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/22 17:54:14 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	freeing(t_mlx *mlx_data)
{
	if (mlx_data->door.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->door.img);
	if (mlx_data->NO.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->NO.img);
	if (mlx_data->SO.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->SO.img);
	if (mlx_data->WE.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->WE.img);
	if (mlx_data->EA.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->EA.img);
	if (mlx_data->door.img)
		mlx_destroy_image(mlx_data->mlx, mlx_data->door.img);
	ft_free_two(mlx_data, mlx_data->map_info.map);
}

void	wall_texture_innit(t_mlx *mlx_data)
{
	mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/WALL1.xpm", &mlx_data->door.width, &mlx_data->door.height);
	if (!mlx_data->door.img)
		freeing(mlx_data);
	mlx_data->NO.img = mlx_xpm_file_to_image(mlx_data->mlx,
			mlx_data->map_info.NO, &mlx_data->NO.width, &mlx_data->NO.height);
	if (!mlx_data->NO.img)
		freeing(mlx_data);
	mlx_data->SO.img = mlx_xpm_file_to_image(mlx_data->mlx,
			mlx_data->map_info.SO, &mlx_data->SO.width, &mlx_data->SO.height);
	if (!mlx_data->SO.img)
		freeing(mlx_data);
	mlx_data->WE.img = mlx_xpm_file_to_image(mlx_data->mlx,
			mlx_data->map_info.WE, &mlx_data->WE.width, &mlx_data->WE.height);
	if (!mlx_data->WE.img)
		freeing(mlx_data);
	mlx_data->EA.img = mlx_xpm_file_to_image(mlx_data->mlx,
			mlx_data->map_info.EA, &mlx_data->EA.width, &mlx_data->EA.height);
	if (!mlx_data->EA.img)
		freeing(mlx_data);
}

void	texture_init(t_mlx *mlx_data)
{
	wall_texture_innit(mlx_data);
	torch_texture_innit(mlx_data);
	get_img_addr(mlx_data);
}
