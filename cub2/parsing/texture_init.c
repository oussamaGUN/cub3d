/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:13:53 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/18 14:55:29 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void get_img_addr(t_mlx *mlx_data)
{
    mlx_data->NO.addr = mlx_get_data_addr(mlx_data->NO.img, &mlx_data->NO.bits_per_pixel, &mlx_data->NO.line_length, &mlx_data->NO.endian);
    mlx_data->WE.addr = mlx_get_data_addr(mlx_data->WE.img, &mlx_data->WE.bits_per_pixel, &mlx_data->WE.line_length, &mlx_data->WE.endian);
    mlx_data->SO.addr = mlx_get_data_addr(mlx_data->SO.img, &mlx_data->SO.bits_per_pixel, &mlx_data->SO.line_length, &mlx_data->SO.endian);
    mlx_data->EA.addr = mlx_get_data_addr(mlx_data->EA.img, &mlx_data->EA.bits_per_pixel, &mlx_data->EA.line_length, &mlx_data->EA.endian);
}
void texture_init(t_mlx *mlx_data)
{
    mlx_data->NO.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.NO, &mlx_data->NO.width, &mlx_data->NO.height);
    mlx_data->SO.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.SO, &mlx_data->SO.width, &mlx_data->SO.height);
    mlx_data->WE.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.WE, &mlx_data->WE.width, &mlx_data->WE.height);
    mlx_data->EA.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.EA, &mlx_data->EA.width, &mlx_data->EA.height);
    get_img_addr(mlx_data);
}