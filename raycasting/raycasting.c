#include "../main.h"

void drawing_square(t_mlx *mlx_data, int color)
{

    int x = mlx_data->position.x;
    int i;
    int j;
    for (i = mlx_data->position.x; i <= x + 30; i++)
    {
        for (j = mlx_data->position.y; j <= x + 30; j++)
        {
            mlx_pixel_put(mlx_data->mlx, mlx_data->mlx_win, i, j, color);
        }
    }
}

void ray_casting(t_mlx *mlx_data, int ac, char **av)
{
    mlx_data->imgs.img = mlx_xpm_file_to_image(mlx_data->mlx
        , "imgs/small_grid.xpm", &mlx_data->mlx_win_height, &mlx_data->mlx_win_width);
    mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, mlx_data->imgs.img, 0, 0);
    int fd = open(av[1], O_RDONLY);
    if (fd == -1)
        exit(1);
    char buffer[10];
    int byte;
    mlx_data->position.x = 0;
    mlx_data->position.y = 0;
    while ((byte = read(fd, buffer, 1)))
    {
        buffer[byte] = '\0';
        if (buffer[0] == '1')
            drawing_square(mlx_data, 0x000000);
        else if (buffer[0] == '0')
            drawing_square(mlx_data, 0xFFFFFF);
        else if (buffer[0] == 'P')
            drawing_square(mlx_data, 0xFF5733);
        mlx_data->position.x += 30;
        if (buffer[0] == '\n')
        {
            mlx_data->position.x = 0;
            mlx_data->position.y += 30;
        }
    }
}