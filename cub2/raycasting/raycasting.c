/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:31:10 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/14 23:52:06 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int IsPlayer(char c)
{
	if (c == 'N' || c == 'S' \
		|| c == 'E' || c == 'W')
		{
			return (1);
		}
	return (0);
}

t_cordonate GetPlayerPosition(char **map)
{
    int i;
    int j;
    t_cordonate pos;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (IsPlayer(map[i][j]))
            {
                pos.x = j * SCALE;
                pos.y = i * SCALE;
                return (pos);
            }
            j++;
        }
        i++;
    }
    return (pos);
}

void PlayerAdder(t_mlx *data)
{
    int x;
    int y;
    int r;
    int x0;
    int y0;

    r = 2;
    x0 = data->Player.x ;//+ SCALE / 2;
    y0 = data->Player.y ;//+ SCALE / 2;
    y = y0 - r;
    while ( y <= y0 + r)
    {
        x = x0 - r;
        while ( x <= x0 + r)
        {
            if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r)
                my_mlx_pixel_put(data, x, y, 0xE91111, 2);
            x++;
        }
        y++;
    }
    // playerDirection.x = cos(data->map_info.direction);
    // playerDirection.y = sin(data->map_info.direction);
    // if (dot(playerDirection, t_vector{1, 0}) == data->map_info.direction)
    // {}

}

double dot(t_vector v1, t_vector v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

t_vector Unit(t_vector vect)
{
    t_vector vector;
    double magnitude = sqrt(vect.x * vect.x + vect.y * vect.y);
    vector.x = vect.x / magnitude;
    vector.y = vect.y / magnitude;
    return (vector);
}

int are_angles_close(double angle1, double angle2, double diff)
{
    double difference = fabs(angle1 - angle2);
    return difference < diff || fabs(difference - 2 * M_PI) < diff;
}

int	is_unit(int i, int j, t_cordonate Player)
{
	double	dx;
	double	dy;
	double	D;

	dx = fabs(i - Player.x);
	dy = fabs(j - Player.y);
	D = dx * dx + dy * dy;
	return (sqrt(D) <= SCALE);
}

void DirectionAdder(t_mlx *data)
{
    int i;
	int j;
    t_vector origine;
    t_vector vect;
	double angle;
    double diff;

	origine.x = 1;
	origine.y = 0;
	diff = 0.1;
	i = 0;
    while (i < data->map_info.height * SCALE)
    {
		j = 0;
        while ( j < data->map_info.width * SCALE)
        {
            vect.x = j - data->Player.x;
            vect.y = i - data->Player.y;
            vect = Unit(vect);
            angle = atan2(vect.y, vect.x);
            // angle = dot(vect, origine);
            if (is_unit(i, j, data->Player) && are_angles_close(angle, data->map_info.direction, diff))
            {
				data->ToMouve.x = i;
				data->ToMouve.y = j;
                my_mlx_pixel_put(data, j, i, GRAY, 2);
            }
			j++;
        }
		i++;
    }
}

int	IsWall(t_cordonate Inter, char **map)
{
	return (map[(int)(Inter.x / SCALE)][(int)(Inter.y / SCALE)] == '1');
}


void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color, int wind)
{
    double dx = abs(x1 - x0);
    double dy = abs(y1 - y0);
    double sx = (x0 < x1) ? 1 : -1;
    double sy = (y0 < y1) ? 1 : -1;
    double err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(mlx, x0, y0, color, wind);

        if (x0 == x1 && y0 == y1) break;
        double e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

//// end test function

///////////////////////////

int	is_wall(t_mlx *data, t_cordonate A)
{
	long long	x;
	long long	y;
    char **map;

    map = data->map_info.map;
	x = A.x /SCALE;
	y = A.y / SCALE;
    if (x < 0 || y < 0 || x >= data->map_info.width || y >= data->map_info.height || map[y][x] == '1')
	    return (1);
    // if (((A.y + 1) / SCALE < data->map_info.height &&  map[(long long)((A.y + 1)/SCALE)][(long long)(A.x / SCALE)] == '1') ||\
    //      ((A.x + 1) / SCALE < data->map_info.width && map[(long long)((A.y)/SCALE)][(long long)((A.x + 1) / SCALE)] == '1'))
    //      {
    //          return (1);
    //      }
    return (0);
}

t_cordonate	HorizontalIntersection(t_mlx *data, double angle_dif)
{
    t_cordonate  A; // firstInterHorizontale
    t_cordonate  P;
	t_cordonate	deff;
    double      angle;

	P.x = data->Player.x ;
	P.y = data->Player.y ;
    angle = (data->map_info.direction + angle_dif);
    if (angle > 2 * M_PI)
        angle -= 2 * M_PI;
	if (tan(angle) == 0)
	{
        A.x = 0;
        A.y = 0;
		A.dist = INT_MAX * 1.;
		return (A);
	}
    if (angle >= 0 && angle < M_PI) // ray facing down
    {
        A.y = floor(P.y / SCALE) * SCALE + SCALE;
		deff.y = SCALE;
    }
    else  // ray facing up
    {
        A.y = floor(P.y / SCALE) * SCALE - 0.00001;
		deff.y = -1 * SCALE;
    }
    A.x = ((A.y - P.y) / tan (angle)) + P.x;
	deff.x = deff.y / tan(angle);
	while (!is_wall(data, A))
	{
		A.x += deff.x;
		A.y += deff.y;
    }
	A.dist = sqrt((A.x - P.x) * (A.x - P.x) + (A.y - P.y) * (A.y - P.y));
	return (A);
}

t_cordonate	VerticalIntersection(t_mlx *data, double angle_dif)
{
    t_cordonate  A;
    t_cordonate  P;
	t_cordonate	deff;
    double      angle;

	P.x = data->Player.x ;
	P.y = data->Player.y ;
    angle = (data->map_info.direction + angle_dif);
    if (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    if (angle > M_PI_2 && angle < 3 *M_PI_2)  // ray facing left
    {
        deff.x = -1 * SCALE;
        A.x = floor(P.x / SCALE) * SCALE - 0.00001;
    }
    else //ray facing right
    {
        deff.x = SCALE;
        A.x = floor(P.x / SCALE) * SCALE + SCALE;
    }
    A.y = P.y - (P.x - A.x) * tan(angle);
    deff.y = deff.x * tan(angle);
    int i = 0;
    while (!is_wall(data, A))
    {
		A.x += deff.x;
		A.y += deff.y;
    }
    A.dist = sqrt((A.x - P.x) * (A.x - P.x) + (A.y - P.y) * (A.y - P.y));
    // if (A.x < 0 || A.y < 0 || A.x >= (double)data->map_info.width || A.y >= (double)data->map_info.height)
    //     A.dist = INT_MAX * 1.;
    return (A);
}

t_cordonate min_of(t_cordonate A, t_cordonate B)
{
    if (A.dist < B.dist)
        return (A);
    return (B);
}

t_cordonate max_of(t_cordonate A, t_cordonate B)
{
    if (A.dist > B.dist)
        return (A);
    return (B);
}

void   RayCasting(t_mlx *data)
{
	t_cordonate	InterSectionH;
	t_cordonate	InterSectionV;
    t_cordonate InterSection;
    double      i;
    t_cordonate P;
    double      wall;

    P.x = data->Player.x;
    P.y = data->Player.y;
    i = -0.523599;
    int X = 0;
    while (i <= 0.523599)
    {
        InterSectionH = HorizontalIntersection(data, i);
        InterSectionV = VerticalIntersection(data, i);
        InterSection = min_of(InterSectionH, InterSectionV);
        if (InterSection.x < 0 || InterSection.y < 0)
            InterSection = max_of(InterSectionH, InterSectionV);
        if (InterSection.dist > 0)
        {
            wall = (SCALE / 3 * HEIGHT / InterSection.dist) / cos(fabs(i));
            if ((HEIGHT / 2) - wall > 0 && (HEIGHT / 2) + wall < HEIGHT)
            {
                draw_line(data, X, 0, X, (HEIGHT / 2) - wall , data->ceil.color, 3);
                draw_line(data, X, (HEIGHT / 2) - wall, X, (HEIGHT / 2) + wall , 0xED0101, 3);    
                draw_line(data, X, (HEIGHT / 2) + wall, X, HEIGHT ,data->floor.color, 3);    
            }
            else
                draw_line(data, X, 0, X, HEIGHT  , 0xED0101, 3);
        }
        else
            {
            draw_line(data, X, 0, X, HEIGHT  , 0xED0101, 3);    
            }
        draw_line(data, P.x, P.y, InterSection.x, InterSection.y, 0x000, 2);
        // draw_line(data, P.x, P.y, InterSection.x, InterSection.y, 0xFFFF, 3);
        
        i += (M_PI / 3) / (WIDTH - 1.);
        X++;
    }
}

void    StandardMap(t_mlx *data)
{
    int         i;
    int         j;

    i = 0;
    while (i < data->map_info.height * SCALE)
    {
        j = 0;
        while (j < data->map_info.width * SCALE)
        {
            if (i % SCALE == 0 || j % SCALE == 0)
                 my_mlx_pixel_put(data, j, i, 0x767676, 2);
            else if (data->map_info.map[i / SCALE][j / SCALE] == '1')//
                my_mlx_pixel_put(data, j, i, 0x00ff, 2);
            else if ((i / SCALE) < data->map_info.height && (j / SCALE) < data->map_info.width &&
                 data->map_info.map[i / SCALE][j / SCALE] == '1')
                my_mlx_pixel_put(data, j, i, 0x00ff, 2);
            else if (data->map_info.map[i / SCALE][j / SCALE] == '0' \
                    || IsPlayer(data->map_info.map[i / SCALE][j / SCALE]))
                my_mlx_pixel_put(data, j, i, 0xFFFFFF, 2);
            else
                my_mlx_pixel_put(data, j , i , 0x0, 2);
            j++;
        }
        i++;
    }
    i = 0;
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            my_mlx_pixel_put(data, j , i , 0x0, 3);
            j++;
        }
        i++;
    }
    PlayerAdder(data);
    // DirectionAdder(data);
    RayCasting(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win3d, data->img3d, 0, 0);
}
