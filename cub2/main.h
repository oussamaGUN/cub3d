#ifndef MAIN_H
#define MAIN_H

#  define BUFFER_SIZE 42
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
// #include <mlx.h>
// #include <X11/X.h>
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
    int texture_number;
    char *line;
    int height;
    int width;
    int arr_len;
    char *mapstr;
}t_map_info;

typedef struct s_vars
{
    int x;
    int y;
    int length;
    char *ft_split;
}t_vars;
typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    t_map_file map_file;
    t_map_info map_info;
    t_vars vars;
}t_mlx;
// parsing functions
char	*get_next_line(int fd);
void parsing(t_mlx *mlx_data);
void reading_textures(t_mlx *mlx_data);
void parsing_map(t_mlx *mlx_data);
void map_rules(t_mlx *mlx_data);
int line_rules(t_mlx *mlx_data);
void free_split(char **split);
void free_infos(t_mlx *mlx_data);
int line_rules(t_mlx *mlx_data);
void map_rules(t_mlx *mlx_data);
int ft_arrlen(char **map);
int ft_check_extension(char *str, char *ext);
void ft_free_one(t_mlx *mlx_data, char *line, char *parse_msg);
void ft_free_two(t_mlx *mlx_data, char **split);
#endif 