/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:30:35 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/22 14:56:39 by ousabbar         ###   ########.fr       */
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
