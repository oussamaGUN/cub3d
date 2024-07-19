/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:31:10 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/19 12:24:30 by afadouac         ###   ########.fr       */
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

void    ranging(int *x0, int *y0, int *x1, int *y1)
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

void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color, int wind)
{
    double dx;;
    double dy;
    double sx;
    double sy;
    double err;

    ranging(&x0, &y0, &x1, &y1);
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    err = dx - dy;
    if (x0 < x1)
       sx = 1;
    else
       sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;
    while (1)
    {
        my_mlx_pixel_put(mlx, x0, y0, color, wind);

        if (x0 == x1 && y0 == y1)
            break;
        if (2 * err > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (2 * err < dx)
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
    if (map[y][x] == 'D')
        return (2);
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
    // A.view = angle;
	if (tan(angle) == 0)
	{
        A.x = 0;
        A.y = 0;
		A.dist = INT_MAX * 1.;
		return (A);
	}
    if (angle >= 0 && angle < M_PI) // ray facing down
    {
        A.view = DOWN;
        A.y = floor(P.y / SCALE) * SCALE + SCALE;
		deff.y = SCALE;
    }
    else  // ray facing up
    {
        A.view = UP;
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
    if (is_wall(data, A) == 2)
        A.view = DOOR;
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
    A.view = angle;
    if (angle > M_PI_2 && angle < 3 *M_PI_2)  // ray facing left
    {
        A.view = LEFT;
        deff.x = -1 * SCALE;
        A.x = floor(P.x / SCALE) * SCALE - 0.00001;
    }
    else //ray facing right
    {
        A.view = RIGHT;
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
    if (is_wall(data, A) == 2)
        A.view = DOOR;
    A.dist = sqrt((A.x - P.x) * (A.x - P.x) + (A.y - P.y) * (A.y - P.y));
    return (A);
}

t_cordonate min_of(t_cordonate H, t_cordonate V)
{
    if (H.dist < V.dist)
    {
        return (H);
    }
    return (V);
}

t_cordonate max_of(t_cordonate H, t_cordonate V)
{
    if (H.dist > V.dist)
    {
        return (H);
    }
    return (V);
}

int get_texel(t_mlx *data ,t_texture texture, int x, int y)
{
	char	*pixel;

    if (x < 0 || y < 0 || x >= texture.width || y >= texture.height)
        return (0);
		pixel = texture.addr + (y * texture.line_length + x * \
			(texture.bits_per_pixel / 8));
		return (*(unsigned int *)pixel);
}

void putingTexture(t_mlx *data, double wall, t_cordonate Intersection, int x)
{
    int color;
    int j;
    int tex_x;
    int tex_y;
    t_texture tex;

    if (Intersection.view == UP)
        tex = data->NO;
    else if (Intersection.view == DOWN)
        tex = data->SO;
    else if (Intersection.view == LEFT)
        tex = data->EA;
    else if (Intersection.view == RIGHT)
        tex = data->WE;
    if (Intersection.view == LEFT || Intersection.view == RIGHT)
    {
        tex_x = fabs(fmod(Intersection.y, SCALE) / SCALE) * tex.width; // Vertical wall
    }
    else
    {
        tex_x = fabs(fmod(Intersection.x, SCALE) / SCALE) * tex.width; // Horizontal wall
    }

    int point_y = (HEIGHT / 2) - wall + data->jump;

    int end = (HEIGHT / 2) + wall + data->jump;
    j = 0;
    while (point_y < end)
    {
        tex_y = (j * tex.height) / (2 * wall); 
        color = get_texel(data, tex, tex_x, tex_y);
        my_mlx_pixel_put(data, x, point_y, color, 3);
        point_y++;
        j++;
    }
}

void   RayCasting(t_mlx *data)
{
    t_cordonate InterSection;
    t_cordonate P;
    double      i;
    double      wall;

    P.x = data->Player.x;
    P.y = data->Player.y;
    i = -0.523599;
    int X = 0;
    // double best = 0.523599; 
    // double best2 = -0.523599; 
    while (i <= 0.523599)
    {
        InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
        // if (InterSection.x < 0 || InterSection.y < 0)
        //     InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
        wall = (SCALE / 3 * HEIGHT / InterSection.dist) / cos(fabs(i));
        if (i <= 0.000409 && i >= -0.000410)
            data->face = InterSection.view;
            draw_line(data, X, 0, X, (HEIGHT / 2) - wall + data->jump, data->ceil.color, 3);
            
            putingTexture(data, wall, InterSection, X);
            ///this line going to be delleted
            // draw_line(data, X, (HEIGHT / 2) - wall + data->jump, X, (HEIGHT / 2) + wall + data->jump , 0xED0101, 3);    
            ///
            draw_line(data, X, (HEIGHT / 2) + wall + data->jump, X, HEIGHT ,data->floor.color, 3);    
        i += (M_PI / 3) / (WIDTH - 1.);
        X++;
    }
    if (data->face == UP)
        puts("UP");
    else if (data->face == DOWN)
        puts("DOWN");
    else if (data->face == LEFT)
        puts("LEFT");
    else if (data->face == RIGHT)
        puts("RIGHT");
}

void    AddDirection(t_mlx *data, int W, int H)
{
    t_cordonate Player;
    t_cordonate dist;
    double length;

    Player.x = WIDTH - W / 2 - 5;
    Player.y = HEIGHT - H / 2 - 5;
    length = 18;
    dist.x = Player.x + length * cos(data->map_info.direction);
    dist.y = Player.y + length * sin(data->map_info.direction);
    draw_line(data, Player.x, Player.y, dist.x, dist.y, 0xEE1D1D, 3);
}

void    DrowMiniMap(t_mlx *data, int W, int H)
{
    int         i;
    int         j;
    int         x;
    int         y;

    i = 0;
    while (i < data->map_info.height * SCALE)
    {
        j = 0;
        while (j < data->map_info.width * SCALE)
        {
            x = j - (data->Player.x - W / 2) + WIDTH - W - 5;
            y = i - (data->Player.y - H / 2) + HEIGHT - H - 5;
            if (i >= data->Player.y - H / 2 && i <= data->Player.y + H / 2 && j >= data->Player.x - W / 2 && j <= data->Player.x + W / 2 )
            {
                if (i % SCALE == 0 || j % SCALE == 0)
                    my_mlx_pixel_put(data, x, y, 0x767676, 3);
                else if (i >= data->Player.y - 3 && i <= data->Player.y + 3 && j >= data->Player.x - 3 && j <= data->Player.x + 3)
                    my_mlx_pixel_put(data, x, y, 0xEE1D1D, 3);
                else if (data->map_info.map[i / SCALE][j / SCALE] == '1')//
                    my_mlx_pixel_put(data, x, y, 0x00ff, 3);
                else if ((i / SCALE) < data->map_info.height && (j / SCALE) < data->map_info.width &&
                    data->map_info.map[i / SCALE][j / SCALE] == '1')
                    my_mlx_pixel_put(data, x, y, 0x00ff, 3);
                else if (data->map_info.map[i / SCALE][j / SCALE] == '0' \
                        || IsPlayer(data->map_info.map[i / SCALE][j / SCALE]))
                    my_mlx_pixel_put(data, x, y, 0xFFFFFF, 3);
                else
                    my_mlx_pixel_put(data, x, y, 0x0, 3);
            }
            j++;
        }
        i++;
    }
}

void    StandardMap(t_mlx *data)
{

    RayCasting(data);
    if (data->map_info.maptype == 1)
    {
        DrowMiniMap(data,  MINIW, MINIH);
        // AddDirection(data, MINIW, MINIH);
    }
    else
    {
        DrowMiniMap(data, MINIW2, MINIH2);
        // AddDirection(data, MINIW2, MINIH2);
    }
    mlx_put_image_to_window(data->mlx, data->win3d, data->img3d, 0, 0);
}
