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

typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    int mlx_win_height;
    int mlx_win_width;
    t_vars vars;
    t_imgs imgs;
    t_movement movement;
    t_position position;
} t_mlx;

void ray_casting(t_mlx *mlx_data, int ac, char **av);

#endif