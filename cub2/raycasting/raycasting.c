/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:31:10 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/25 17:30:51 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	RayCasting(t_mlx *data)
{
	t_cordonate	InterSection;
	double		i;
	double		wall;
	int			X;

	i = -0.523599;
	X = 0;
	fillmouves(data);
	drow_floor(data,data->floor.color);
	while (i <= 0.523599)
	{
		InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
		if (i <= 0.000409 && i >= -0.000410)
			data->face = InterSection.view;
		wall = (SCALE / 3 * HEIGHT / InterSection.dist) / cos(fabs(i));
		drow_ciell(data, X, (HEIGHT / 2) - wall + data->jump, data->ceil.color);
		putingTexture(data, wall, InterSection, X);
		i += (M_PI / 3) / (WIDTH - 1.);
		X++;
	}
}

void	StandardMap(t_mlx *data)
{
	RayCasting(data);
	DrowMiniMap(data);
	if (data->map_info.maptype == 1)
	{
		AddDirection(data, MINIW, MINIH);
	}
	else
	{
		AddDirection(data, MINIW2, MINIH2);
	}
	mlx_put_image_to_window(data->mlx, data->win3d, data->img3d, 0, 0);
}
