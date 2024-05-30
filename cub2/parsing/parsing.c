#include "../main.h"

void file_opennig(t_mlx *mlx_data)
{
    mlx_data->map_file.fd = open(mlx_data->map_file.av, O_RDONLY);
    if (mlx_data->map_file.fd == -1)
    {
        printf("file not found\n");
        exit(1);
    }
}

void vars_init(t_mlx *mlx_data)
{
    mlx_data->map_info.C = NULL;
    mlx_data->map_info.F = NULL;
    mlx_data->map_info.EA = NULL;
    mlx_data->map_info.NO = NULL;
    mlx_data->map_info.SO = NULL;
    mlx_data->map_info.WE = NULL;
    mlx_data->map_info.map_index = 0;
}


void parsing(t_mlx *mlx_data)
{
    vars_init(mlx_data);
    file_opennig(mlx_data);
    reading_textures(mlx_data);
    parsing_map(mlx_data);
    close(mlx_data->map_file.fd);
}