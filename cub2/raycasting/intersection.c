/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:13:21 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/24 23:45:01 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_cordonate	init_H_intersection(t_cordonate P, double angle, t_cordonate *deff)
{
	t_cordonate	A;

	if (tan(angle) == 0)
	{
		A.x = 0;
		A.y = 0;
		A.dist = INT_MAX * 1.;
		return (A);
    }
	if (angle >= 0 && angle < M_PI)
	{
		A.view = DOWN;
		A.y = floor(P.y / SCALE) * SCALE + SCALE;
		deff->y = SCALE;
	}
	else
	{
		A.view = UP;
		A.y = floor(P.y / SCALE) * SCALE - 0.0000001;
		deff->y = -1 * SCALE;
	}
	A.x = ((A.y - P.y) / tan(angle)) + P.x;
	deff->x = deff->y / tan(angle);
	return (A);
}

t_cordonate	HorizontalIntersection(t_mlx *data, double angle_dif)
{
	t_cordonate	A;
	t_cordonate	P;
	t_cordonate	deff;
	double		angle;

	P.x = data->Player.x ;
	P.y = data->Player.y ;
	angle = (data->map_info.direction + angle_dif);
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	A.view = angle;
	A = init_H_intersection(P, angle, &deff);
	A.x = ((A.y - P.y) / tan (angle)) + P.x;
	deff.x = deff.y / tan(angle);
	while (!is_wall(data, &A))
	{
		A.x += deff.x;
		A.y += deff.y;
	}
	A.dist = sqrt((A.x - P.x) * (A.x - P.x) + (A.y - P.y) * (A.y - P.y));
	return (A);
}

void	init_V_intersection(t_cordonate P, double angle, t_cordonate *A, t_cordonate *deff)
{
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		A->view = LEFT;
		deff->x = -1 * SCALE;
		A->x = floor(P.x / SCALE) * SCALE - 0.0000001;
	}
	else
	{
		A->view = RIGHT;
		deff->x = SCALE;
		A->x = floor(P.x / SCALE) * SCALE + SCALE;
	}
	A->y = P.y - (P.x - A->x) * tan(angle);
	deff->y = deff->x * tan(angle);
}


t_cordonate	VerticalIntersection(t_mlx *data, double angle_dif)
{
	t_cordonate	A;
	t_cordonate	P;
	t_cordonate	deff;
	double		angle;

	P.x = data->Player.x ;
	P.y = data->Player.y ;
	angle = (data->map_info.direction + angle_dif);
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	init_V_intersection(P, angle, &A, &deff);
	A.y = P.y - (P.x - A.x) * tan(angle);
	deff.y = deff.x * tan(angle);
	while (!is_wall(data, &A))
	{
		A.x += deff.x;
		A.y += deff.y;
	}
	A.dist = sqrt((A.x - P.x) * (A.x - P.x) + (A.y - P.y) * (A.y - P.y));
	return (A);
}
