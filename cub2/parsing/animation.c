/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:30:35 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/24 12:29:12 by ousabbar         ###   ########.fr       */
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
		torch_puts(mlx_data, 6, 65);
	return (frame);
}

int	frame_num_two(t_mlx *mlx_data, int frame)
{
	if (frame < 70)
		torch_puts(mlx_data, 7, 60);
	else if (frame < 80)
	{
		torch_puts(mlx_data, 8, 55);
		if (frame == 79)
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

void first_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 5)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/1.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 10)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/2.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 15)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/3.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}
void second_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 20)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/4.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 25)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/5.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 30)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/6.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}

void third_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 35)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/7.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 40)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/8.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 45)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/9.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}

void fifth_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 50)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/10.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else  if (frame < 55)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/11.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 60)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/12.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}
void sixth_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 65)
{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/13.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 70)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/14.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 75)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/15.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}
void eighth_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 80)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/16.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 85)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/17.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 90)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/18.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}
void ninth_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 95)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/19.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 100)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/20.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
	else if (frame < 105)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/21.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}
}
int tenth_door_frame(t_mlx *mlx_data, int frame)
{
	if (frame < 110)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/22.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
	}	
	else if (frame < 115)
	{
		mlx_data->door.img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/game_texture/23.xpm", &mlx_data->door.width,
			&mlx_data->door.height);
		if (!mlx_data->door.img)
			freeing(mlx_data);
		if (frame == 114)
			frame = 0;
	}
	return (frame);
}
void get_door_addr(t_mlx *mlx_data)
{
	mlx_data->door.addr = mlx_get_data_addr(mlx_data->door.img,
		&mlx_data->door.bits_per_pixel, &mlx_data->door.line_length,
		&mlx_data->door.endian);
	if (!mlx_data->door.addr)
		freeing(mlx_data);
}
int gate_animation(t_mlx *mlx_data)
{
	static int frame = 0;

	mlx_destroy_image(mlx_data->mlx, mlx_data->door.img);	
	if (frame < 15)
		first_door_frame(mlx_data, frame);
	else if (frame < 30)
		second_door_frame(mlx_data, frame);
	else if (frame < 45)
		third_door_frame(mlx_data, frame);
	else if (frame < 60)
		fifth_door_frame(mlx_data, frame);
	else if (frame < 75)
		sixth_door_frame(mlx_data, frame);
	else if (frame < 90)
		eighth_door_frame(mlx_data, frame);
	else if (frame < 100)
		ninth_door_frame(mlx_data, frame);
	else if (frame < 115)
		frame = tenth_door_frame(mlx_data, frame);
	get_door_addr(mlx_data);
	frame++;
	return (0);
}
