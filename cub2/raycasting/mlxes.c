/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:06:05 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/04 19:33:10 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * \
		(data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}
