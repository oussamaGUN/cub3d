/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:40:31 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/22 14:44:46 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	wall_texture_get_img_addr(t_mlx *mlx_data)
{
	mlx_data->NO.addr = mlx_get_data_addr(mlx_data->NO.img,
			&mlx_data->NO.bits_per_pixel, &mlx_data->NO.line_length,
			&mlx_data->NO.endian);
	if (!mlx_data->NO.addr)
		freeing(mlx_data);
	mlx_data->WE.addr = mlx_get_data_addr(mlx_data->WE.img,
			&mlx_data->WE.bits_per_pixel, &mlx_data->WE.line_length,
			&mlx_data->WE.endian);
	if (!mlx_data->WE.addr)
		freeing(mlx_data);
	mlx_data->SO.addr = mlx_get_data_addr(mlx_data->SO.img,
			&mlx_data->SO.bits_per_pixel, &mlx_data->SO.line_length,
			&mlx_data->SO.endian);
	if (!mlx_data->SO.addr)
		freeing(mlx_data);
	mlx_data->EA.addr = mlx_get_data_addr(mlx_data->EA.img,
			&mlx_data->EA.bits_per_pixel, &mlx_data->EA.line_length,
			&mlx_data->EA.endian);
	if (!mlx_data->EA.addr)
		freeing(mlx_data);
	mlx_data->door.addr = mlx_get_data_addr(mlx_data->door.img,
			&mlx_data->door.bits_per_pixel, &mlx_data->door.line_length,
			&mlx_data->door.endian);
	if (!mlx_data->door.addr)
		freeing(mlx_data);
}

void	torch_texture_get_img_addr(t_mlx *mlx_data)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		if (i == 2)
			i++;
		mlx_data->torch[i].addr = mlx_get_data_addr(mlx_data->torch[i].img,
				&mlx_data->torch[i].bits_per_pixel,
				&mlx_data->torch[i].line_length,
				&mlx_data->torch[i].endian);
		if (!mlx_data->torch[i].addr)
			freeing(mlx_data);
		i++;
	}
}

void	get_img_addr(t_mlx *mlx_data)
{
	wall_texture_get_img_addr(mlx_data);
	torch_texture_get_img_addr(mlx_data);
}
