#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <X11/X.h>
#include <fcntl.h>
#include "libft/libft.h"

# define UP 119
# define LEFT 97
# define DOWN 115
# define RIGHT 100
# define ESC 65307
# define PLAYER_SPEED 1

typedef struct s_movement
{
    int x_movement;
    int y_movement;
}t_movement;
typedef struct s_vars
{
    char *map;
}t_vars;

typedef struct s_imgs
{
    void *img;
    void *vi;
}t_imgs;

typedef struct s_position
{
    int x;
    int y;
}t_position;

typedef struct s_files
{
    int fd;
    char *file_content;
}t_files;

typedef struct s_player
{
    int x;
    int y;
}t_player;
typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    int mlx_win_height;
    int mlx_win_width;
    t_files fds;
    t_vars vars;
    t_imgs imgs;
    t_movement movement;
    t_position position;
    t_player player;
} t_mlx;

void map(t_mlx *mlx_data);
void drawing_square(t_mlx *mlx_data, int color);
void updating_position(t_mlx *mlx_data, int color);
void player_position(t_mlx *mlx_data);
void draw(t_mlx *mlx_data);

#endif