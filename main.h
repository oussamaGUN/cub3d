#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <X11/X.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_vars
{
    char *map;
}t_vars;

typedef struct s_imgs
{
    void *img;
    void *vi;
}t_imgs;

typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    int mlx_win_height;
    int mlx_win_width;
    t_vars vars;
    t_imgs imgs;
} t_mlx;

char *ray_casting(t_mlx *mlx_data, int ac, char **av);

#endif