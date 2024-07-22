/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:30:35 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/22 18:12:10 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	torch_puts(t_mlx *mlx_data, int pic_num, int up)
{
	int	i;
	int	x;
	int	color;

	i = 0;
	while (i < 800)
	{
		x = 0;
		while (x < 800)
		{
			color = get_texel(mlx_data, mlx_data->torch[pic_num], x, i);
			if (color != 0 && color != -16777216)
				my_mlx_pixel_put(mlx_data, x - 400, i + up, color, 3);
			x++;
		}
		i++;
	}
}

int	frame_num_one(t_mlx *mlx_data, int frame)
{
	if (frame < 10)
		torch_puts(mlx_data, 0, 50);
	else if (frame < 20)
		torch_puts(mlx_data, 1, 55);
	else if (frame < 30)
		torch_puts(mlx_data, 3, 60);
	else if (frame < 40)
		torch_puts(mlx_data, 4, 65);
	else if (frame < 50)
		torch_puts(mlx_data, 5, 70);
	else if (frame < 60)
		torch_puts(mlx_data, 6, 75);
	return (frame);
}

int	frame_num_two(t_mlx *mlx_data, int frame)
{
	if (frame < 70)
		torch_puts(mlx_data, 7, 70);
	else if (frame < 80)
		torch_puts(mlx_data, 8, 65);
	else if (frame < 90)
		torch_puts(mlx_data, 9, 60);
	else if (frame < 100)
		torch_puts(mlx_data, 10, 55);
	else if (frame < 110)
	{
		torch_puts(mlx_data, 11, 50);
		if (frame == 109)
			frame = 0;
	}
	return (frame);
}

int	torch_animation(t_mlx *mlx_data)
{
	static int	frame;

	if (frame < 60)
		frame = frame_num_one(mlx_data, frame);
	else if (frame < 110)
		frame = frame_num_two(mlx_data, frame);
	frame++;
	return (0);
}

int gate_animation(t_mlx *mlx_data)
{
	static int frame = 0;
	if (frame < 8)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door9.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 16)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door8.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 24)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door7.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 32)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door6.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 40)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door5.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 48)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door4.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 56)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door3.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 62)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door2.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 70)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door1.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 78)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/door0.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
		if (frame == 77)
			frame = 0;
	}
	mlx_data->door.addr = mlx_get_data_addr(mlx_data->door.img,
		&mlx_data->door.bits_per_pixel, &mlx_data->door.line_length,
		&mlx_data->door.endian);
	if (!mlx_data->door.addr)
		freeing(mlx_data);
	frame++;
	return (0);
}