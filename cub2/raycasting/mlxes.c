/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:06:05 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/14 13:29:42 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color, int wind)
{
	char	*pixel;

	if (wind == 3)
	{
		pixel = data->addr3d + (y * data->line_length3d + x * \
			(data->bits_per_pixel3d / 8));
		*(unsigned int *)pixel = color;
	}
	else if (wind == 2)
	{
		pixel = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}
