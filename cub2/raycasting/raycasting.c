/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:31:10 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/23 21:59:57 by ousabbar         ###   ########.fr       */
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
    static int counter = 0;

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

int isNeer(t_cordonate *A, t_cordonate Player)
{
    double dist;
    double  diff_x;
    double  diff_y;

    diff_x = A->x - Player.x;
    diff_y = A->y - Player.y;
    dist = sqrt(diff_x * diff_x + diff_y * diff_y);
    return (dist >= DISTDOOR);
}

int	is_wall(t_mlx *data, t_cordonate *A)
{
	long long	x;
	long long	y;
    char **map;

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
        A.y = floor(P.y / SCALE) * SCALE - 0.0000001;
		deff.y = -1 * SCALE;
    }
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
        A.x = floor(P.x / SCALE) * SCALE - 0.0000001;
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
    while (!is_wall(data, &A))
    {
		A.x += deff.x;
		A.y += deff.y;
    }
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

int adjust_alpha(unsigned int color, double dist)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    dist /= DARKFACTOR;
    if (dist > 255)
        dist = 255;
    if (dist < 1.1)
        dist = 1.1;
    r = ((color >> 16) & 0xFF) / dist;
    g = ((color >> 8) & 0xFF) / dist;
    b = (color & 0xFF) / dist;

    return (r << 16) | (g << 8) | b ;
}

void putingTexture(t_mlx *data, double wall, t_cordonate Intersection, int x)
{
    int color;
    int j;
    double tex_x;
    double tex_y;
    double point_y;
    double end;
    t_texture tex;

    if (Intersection.is_door == 1)
        tex = data->door;
    // else if (Intersection.is_door == 2)
    //     return ;
    else if (Intersection.view == UP)
        tex = data->NO;
    else if (Intersection.view == DOWN)
        tex = data->SO;
    else if (Intersection.view == LEFT)
        tex = data->EA;
    else if (Intersection.view == RIGHT)
        tex = data->WE;
    else if (Intersection.view == DOOR)
        tex = data->door;
    if (Intersection.view == LEFT || Intersection.view == RIGHT)
    {
        tex_x = fabs(fmod(Intersection.y, SCALE) / SCALE) * tex.width; // Vertical wall
    }
    else
    {
        tex_x = fabs(fmod(Intersection.x, SCALE) / SCALE) * tex.width; // Horizontal wall
    }

    point_y = (HEIGHT / 2) - wall + data->jump;

    end = (HEIGHT / 2) + wall + data->jump;
    j = 0;
    while (point_y < end)
    {
        tex_y = (j * tex.height) / (2 * wall); 
        color = get_texel(data, tex, tex_x, tex_y);
        color = adjust_alpha(color, Intersection.dist);
        my_mlx_pixel_put(data, x, point_y, color, 3);
        point_y++;
        j++;
    }
}


void    fillmouves(t_mlx *data)
{
    t_cordonate InterSection;
    double      i;

//down
    i =  M_PI;
    InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
    if (InterSection.x < 0 || InterSection.y < 0)
        InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
    data->mouves.down = InterSection.dist;
///up
    i = 0;
    InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
    if (InterSection.x < 0 || InterSection.y < 0)
        InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
    data->mouves.up = InterSection.dist;
///left
    i = -1 * M_PI_2;
    InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
    if (InterSection.x < 0 || InterSection.y < 0)
        InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
    data->mouves.left = InterSection.dist;
///right
    i =  M_PI_2;
    InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
    if (InterSection.x < 0 || InterSection.y < 0)
        InterSection = max_of(HorizontalIntersection(data, i), VerticalIntersection(data, i));
    data->mouves.right = InterSection.dist;
}

void    drow_floor(t_mlx *mlx, int x, int y, int color)
{
    double  dist;

    while (y < HEIGHT)
    {
        my_mlx_pixel_put(mlx, x, y, color, 3);
        y++;
    }
}

void    drow_ciell(t_mlx *mlx, int x, int y, int color)
{
    double  pos;

    pos = 0;
    while (pos < y)
    {
        my_mlx_pixel_put(mlx, x, pos, color, 3);
        pos++;
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
    fillmouves(data);
    while (i <= 0.523599)
    {
        InterSection = min_of(HorizontalIntersection(data, i),VerticalIntersection(data, i));
        if (i <= 0.000409 && i >= -0.000410)
            data->face = InterSection.view;
        wall = (SCALE / 3 * HEIGHT / InterSection.dist) / cos(fabs(i));
        drow_ciell(data, X, (HEIGHT / 2) - wall + data->jump, data->ceil.color);
        
        putingTexture(data, wall, InterSection, X);
        drow_floor(data, X, (HEIGHT / 2) + wall + data->jump, data->floor.color);   
        i += (M_PI / 3) / (WIDTH - 1.);
        X++;
    }
}

void    AddDirection(t_mlx *data, int W, int H)
{
    t_cordonate Player;
    t_cordonate dist;
    double length;

    Player.x = WIDTH - W / 2 - 5;
    Player.y = HEIGHT - H / 2 - 5;
    length = 18;
    // dist.x = Player.x + length * cos(data->map_info.direction);
    // dist.y = Player.y + length * sin(data->map_info.direction);
    int n = 0;
	while (n < 20)
	{
        Player.x += cos(data->map_info.direction);
        Player.y += sin(data->map_info.direction);
        my_mlx_pixel_put(data, Player.x, Player.y, 0xFF, 3);
        n++;
	}
    // draw_line(data, dist.x, dist.y, Player.x, Player.y, 0xEE1D1D, 3);
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
                else if (i >= data->Player.y - 2 && i <= data->Player.y + 2 && j >= data->Player.x - 2 && j <= data->Player.x + 2)
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
        AddDirection(data, MINIW, MINIH);
    }
    else
    {
        DrowMiniMap(data, MINIW2, MINIH2);
        AddDirection(data, MINIW2, MINIH2);
    }
    mlx_put_image_to_window(data->mlx, data->win3d, data->img3d, 0, 0);
}