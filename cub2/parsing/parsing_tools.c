#include "../main.h"

int ft_arrlen(char **map)
{
    int i;
    i = 0;
    while (map[i])
        i++;
    return i;
}

void free_split(char **split)
{
    int i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}

void free_infos(t_mlx *mlx_data)
{
    free(mlx_data->map_info.C);
    free(mlx_data->map_info.F);
    free(mlx_data->map_info.SO);
    free(mlx_data->map_info.NO);
    free(mlx_data->map_info.WE);
    free(mlx_data->map_info.EA);
}
