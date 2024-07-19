/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:13:53 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/19 10:50:43 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void freeing(t_mlx *mlx_data)
{
    printf("error in texture\n");
    if (mlx_data->NO.img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->NO.img);
    if (mlx_data->SO.img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->SO.img);
    if (mlx_data->WE.img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->WE.img);
    if (mlx_data->EA.img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->EA.img);
    ft_free_two(mlx_data, mlx_data->map_info.map);
    exit(1);
}
void get_img_addr(t_mlx *mlx_data)
{
    mlx_data->NO.addr = mlx_get_data_addr(mlx_data->NO.img, &mlx_data->NO.bits_per_pixel, &mlx_data->NO.line_length, &mlx_data->NO.endian);
    if (!mlx_data->NO.addr)
        freeing(mlx_data);
    mlx_data->WE.addr = mlx_get_data_addr(mlx_data->WE.img, &mlx_data->WE.bits_per_pixel, &mlx_data->WE.line_length, &mlx_data->WE.endian);
    if (!mlx_data->WE.addr)
        freeing(mlx_data);
    mlx_data->SO.addr = mlx_get_data_addr(mlx_data->SO.img, &mlx_data->SO.bits_per_pixel, &mlx_data->SO.line_length, &mlx_data->SO.endian);
    if (!mlx_data->SO.addr)
        freeing(mlx_data);
    mlx_data->EA.addr = mlx_get_data_addr(mlx_data->EA.img, &mlx_data->EA.bits_per_pixel, &mlx_data->EA.line_length, &mlx_data->EA.endian);
    if (!mlx_data->EA.addr)
        freeing(mlx_data);
}
void texture_init(t_mlx *mlx_data)
{
    mlx_data->NO.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.NO, &mlx_data->NO.width, &mlx_data->NO.height);
    if (!mlx_data->NO.img)
        freeing(mlx_data);
    mlx_data->SO.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.SO, &mlx_data->SO.width, &mlx_data->SO.height);
    if (!mlx_data->SO.img)
        freeing(mlx_data);
    mlx_data->WE.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.WE, &mlx_data->WE.width, &mlx_data->WE.height);
    if (!mlx_data->WE.img)
        freeing(mlx_data);
    mlx_data->EA.img = mlx_xpm_file_to_image(mlx_data->mlx, mlx_data->map_info.EA, &mlx_data->EA.width, &mlx_data->EA.height);
    if (!mlx_data->EA.img)
        freeing(mlx_data);
    get_img_addr(mlx_data);
}