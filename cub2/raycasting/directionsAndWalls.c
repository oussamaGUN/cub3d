/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directionsAndWalls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:20:07 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/24 23:38:09 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	ranging(int *x0, int *y0, int *x1, int *y1)
{
	if (*x0 < 0)
		*x0 = 0;
	if (*x0 > WIDTH)
		*x0 = WIDTH;
	if (*x1 < 0)
		*x1 = 0;
	if (*x1 > WIDTH)
		*x1 = WIDTH;
	if (*y0 < 0)
		*y0 = 0;
	if (*y0 > HEIGHT)
		*y0 = HEIGHT;
	if (*y1 < 0)
		*y1 = 0;
	if (*y1 > HEIGHT)
		*y1 = HEIGHT;
}

int	isNeer(t_cordonate *A, t_cordonate Player)
{
	double	dist;
	double	diff_x;
	double	diff_y;

	diff_x = A->x - Player.x;
	diff_y = A->y - Player.y;
	dist = sqrt(diff_x * diff_x + diff_y * diff_y);
	return (dist >= DISTDOOR);
}

int	is_wall(t_mlx *data, t_cordonate *A)
{
	long long	x;
	long long	y;
	char		**map;

	map = data->map_info.map;
	A->is_door = 0;
	x = A->x /SCALE;
	y = A->y / SCALE;
	if (x < 0 || y < 0 || x >= data->map_info.width || y >= data->map_info.height || map[y][x] == '1')
		return (1);
	A->is_door = 0;
	if (map[y][x] == 'D' && isNeer(A, data->Player))
	{
		A->is_door = 1;
		return (1);
	}
	return (0);
}

void	fillmouves(t_mlx *data)
{
	t_cordonate	InterSection;
	double		i;

	i =  M_PI;
	InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
	if (InterSection.x < 0 || InterSection.y < 0)
		InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
	data->mouves.down = InterSection.dist;
	i = 0;
	InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
	if (InterSection.x < 0 || InterSection.y < 0)
		InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
	data->mouves.up = InterSection.dist;
	i = -1 * M_PI_2;
	InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
	if (InterSection.x < 0 || InterSection.y < 0)
		InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
	data->mouves.left = InterSection.dist;
	i =  M_PI_2;
	InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
	if (InterSection.x < 0 || InterSection.y < 0)
		InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
	data->mouves.right = InterSection.dist;
}
