#include "../main.h"

char *ray_casting(struct t_mlx *mlx_data)
{
    for (int i = 0; i < mlx_data->mlx_win_height; i++)
    {
        for (int j = 0; j < mlx_data->mlx_win_width; j++)
        {
            mlx_pixel_put(mlx_data->mlx, mlx_data->mlx_winj, i, j, 0x00FF0000);  
        }
        
    }
    return NULL;
}