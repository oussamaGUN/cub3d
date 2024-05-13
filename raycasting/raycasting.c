#include "../main.h"



char *ray_casting(t_mlx *mlx_data, int ac, char **av)
{
    mlx_data->imgs.img = mlx_xpm_file_to_image(mlx_data->mlx
        , "imgs/small_grid.xpm", &mlx_data->mlx_win_height, &mlx_data->mlx_win_width);
    mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, mlx_data->imgs.img, 0, 0);
    mlx_data->imgs.img = mlx_xpm_file_to_image(mlx_data->mlx
        , "imgs/monster.xpm", &mlx_data->mlx_win_height, &mlx_data->mlx_win_width);
    mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, mlx_data->imgs.img, 500, 500);
    return NULL;
}