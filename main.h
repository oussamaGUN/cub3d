#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <X11/X.h>

struct t_mlx
{
    void *mlx;
    void *mlx_win;
    int mlx_win_height;
    int mlx_win_width;
};
char *ray_casting(struct t_mlx *mlx_data);

#endif