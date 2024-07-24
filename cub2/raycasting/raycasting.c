/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:31:10 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/24 21:19:05 by afadouac         ###   ########.fr       */
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

t_cordonate init_H_intersection(t_cordonate P, double angle, t_cordonate *deff)
{
    t_cordonate A;

    if (tan(angle) == 0)
    {
        A.x = 0;
        A.y = 0;
        A.dist = INT_MAX * 1.;
        return A;
    }
    if (angle >= 0 && angle < M_PI) // ray facing down
    {
        A.view = DOWN;
        A.y = floor(P.y / SCALE) * SCALE + SCALE;
        deff->y = SCALE;
    }
    else  // ray facing up
    {
        A.view = UP;
        A.y = floor(P.y / SCALE) * SCALE - 0.0000001;
        deff->y = -1 * SCALE;
    }
    A.x = ((A.y - P.y) / tan(angle)) + P.x;
    deff->x = deff->y / tan(angle);
    return A;
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

void init_V_intersection(t_cordonate P, double angle, t_cordonate *A, t_cordonate *deff)
{
    if (angle > M_PI_2 && angle < 3 * M_PI_2)  // ray facing left
    {
        A->view = LEFT;
        deff->x = -1 * SCALE;
        A->x = floor(P.x / SCALE) * SCALE - 0.0000001;
    }
    else // ray facing right
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
    t_cordonate  A;
    t_cordonate  P;
	t_cordonate	deff;
    double      angle;

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



int shadding(unsigned int color, double dist, int factor)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    dist /= DARKFACTOR * factor;
    if (dist > 255)
        dist = 255;
    if (dist < 1.1)
        dist = 1.1;
    r = ((color >> 16) & 0xFF) / dist;
    g = ((color >> 8) & 0xFF) / dist;
    b = (color & 0xFF) / dist;

    return (r << 16) | (g << 8) | b ;
}

t_texture *init_texture(t_mlx *data, t_cordonate Intersection)
{
    t_texture *tex;
    int         i;
    int         numb;

    if (Intersection.is_door == 1)
        numb = 2;
    else
        numb = 1;
    tex = malloc(sizeof(t_texture) * numb);
    i = 0;
    while (i < numb)
    {
        if (Intersection.view == UP)
            tex[i] = data->NO;
        else if (Intersection.view == DOWN)
            tex[i] = data->SO;
        else if (Intersection.view == LEFT)
            tex[i] = data->EA;
        else if (Intersection.view == RIGHT)
            tex[i] = data->WE;
        i++;
    }
    if (Intersection.is_door == 1)
        tex[1] = data->door;
    return (tex);
}

int max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int    puttexel(t_mlx *data ,t_texture *texture, t_cordonate tex_cord[], int is_door)
{
       int     color[2];
    
        color[0] = get_texel(data, texture[0], tex_cord[0].x, tex_cord[0].y);
        if (is_door == 1)
        {
            color[1] = get_texel(data, texture[1], tex_cord[1].x, tex_cord[1].y);
            color[0] = max(color[0], color[1]);
        }
        return (color[0]);
}

void init_texture_coords(t_cordonate Intersection, t_texture *textures, t_cordonate tex_cord[2])
{
    if (Intersection.view == LEFT || Intersection.view == RIGHT)
    {
        tex_cord[0].x = fabs(fmod(Intersection.y, SCALE) / SCALE) * textures[0].width; // Vertical wall
        if (Intersection.is_door == 1)
            tex_cord[1].x = fabs(fmod(Intersection.y, SCALE) / SCALE) * textures[1].width; // Vertical wall
    }
    else
    {
        tex_cord[0].x = fabs(fmod(Intersection.x, SCALE) / SCALE) * textures[0].width; // Horizontal wall
        if (Intersection.is_door == 1)
            tex_cord[1].x = fabs(fmod(Intersection.x, SCALE) / SCALE) * textures[1].width; // Horizontal wall
    }
}

void putingTexture(t_mlx *data, double wall, t_cordonate Intersection, int x)
{
    int     color;
    t_cordonate tex_cord[2];
    t_cordonate point;
    t_texture *textuere;

    textuere = init_texture(data, Intersection);
    init_texture_coords(Intersection, textuere, tex_cord);
    point.x = (HEIGHT / 2) - wall + data->jump;
    point.y = 0;
    while (point.x < (HEIGHT / 2) + wall + data->jump)
    {
        tex_cord[0].y = (point.y * textuere[0].height) / (2 * wall);
        if (Intersection.is_door == 1)
            tex_cord[1].y =  (point.y * textuere[1].height) / (2 * wall);
        color = puttexel(data, textuere, tex_cord, Intersection.is_door);
        color = shadding(color, Intersection.dist, 1);
        my_mlx_pixel_put(data, x, point.x, color);
        point.x++;
        point.y++;
    }
    free(textuere);
}


void    fillmouves(t_mlx *data)
{
    t_cordonate InterSection;
    double      i;

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


void    drow_floor(t_mlx *mlx, int color)
{
    double  dist;
    int     x;
    int     y;
    int     collor;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            dist = sqrt((x - (WIDTH / 2) + WIDTH / 4) * (x - (WIDTH / 2) + WIDTH / 4) + (y - HEIGHT ) * (y - HEIGHT ));
            collor = shadding(color, dist, 8);
            my_mlx_pixel_put(mlx, x, y, collor);
            x++;
        }
        y++;
    }
}

void    drow_ciell(t_mlx *mlx, int x, int y, int color)
{
    double  pos;

    pos = 0;
    while (pos < y)
    {
        my_mlx_pixel_put(mlx, x, pos, color);
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

void    AddDirection(t_mlx *data, int W, int H)
{
    t_cordonate Player;

    Player.x = WIDTH - W / 2 - 5;
    Player.y = HEIGHT - H / 2 - 5;
    int n = 0;
	while (n < 20)
	{
        Player.x += cos(data->map_info.direction);
        Player.y += sin(data->map_info.direction);
        my_mlx_pixel_put(data, Player.x, Player.y, 0xFF);
        n++;
	}
}

int is_in_range(t_cordonate Player, int maptype, int i, int j)
{
    int     W;
    int     H;

    if (maptype == 1)
    {
        W = MINIW;
        H = MINIH;
    }
    else
    {
        W = MINIW2;
        H = MINIH2;
    }
    
    return (i >= Player.y - H / 2 && i <= Player.y + H / 2 && \
         j >= Player.x - W / 2 && j <= Player.x + W / 2);
}

void    fill_WH(t_cordonate *WH, int maptype)
{
    if (maptype == 1)
    {
        WH->x = MINIW;
        WH->y = MINIH;
    }
    else
    {
        WH->x = MINIW2;
        WH->y = MINIH2;
    }    
}

void    putColorToMini(t_mlx *data, int i, int j)
{
    int x;
    int y;
    t_cordonate WH;

    fill_WH(&WH, data->map_info.maptype);
    x = j - (data->Player.x - WH.x / 2) + WIDTH - WH.x - 5;
    y = i - (data->Player.y - WH.y / 2) + HEIGHT - WH.y - 5;
    if (i % SCALE == 0 || j % SCALE == 0)
        my_mlx_pixel_put(data, x, y, GRAY);
    else if (i >= data->Player.y - 2 && i <= data->Player.y + 2 &&\
         j >= data->Player.x - 2 && j <= data->Player.x + 2)
        my_mlx_pixel_put(data, x, y, 0xEE1D1D);
    else if (data->map_info.map[i / SCALE][j / SCALE] == '1')//
        my_mlx_pixel_put(data, x, y, 0x00ff);
    else if ((i / SCALE) < data->map_info.height && (j / SCALE) < data->map_info.width &&
        data->map_info.map[i / SCALE][j / SCALE] == '1')
        my_mlx_pixel_put(data, x, y, 0x00ff);
    else if (data->map_info.map[i / SCALE][j / SCALE] == '0' \
            || IsPlayer(data->map_info.map[i / SCALE][j / SCALE]))
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
    else if (data->map_info.map[i / SCALE][j / SCALE] == 'D')//
        my_mlx_pixel_put(data, x, y, 0x00FFFF);
    else
        my_mlx_pixel_put(data, x, y, 0x0);
}

void    DrowMiniMap(t_mlx *data)
{
    int         i;
    int         j;

    i = 0;
    while (i < data->map_info.height * SCALE)
    {
        j = 0;
        while (j < data->map_info.width * SCALE)
        {
            if (is_in_range(data->Player, data->map_info.maptype, i, j))
                putColorToMini(data, i, j);
            j++;
        }
        i++;
    }
}

void    StandardMap(t_mlx *data)
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