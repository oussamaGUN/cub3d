#ifndef MAIN_H
#define MAIN_H

#  define BUFFER_SIZE 42
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <X11/X.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_map_file
{
    int fd;
    char *av;
}t_map_file;

typedef struct s_map_info
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *F;
    char *C;
    char **map;
    int map_index;
    char *line;
}t_map_info;

typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    t_map_file map_file;
    t_map_info map_info;
}t_mlx;
// parsing functions
char	*get_next_line(int fd);
void parsing(t_mlx *mlx_data);
#endif 