#include "main.h"


void drawing_square(t_mlx *mlx_data, int color)
{

    int start_x = mlx_data->position.x;
    int start_y = mlx_data->position.y;
    
    for (int i = start_x; i <= start_x + 30; i++)
    {
        for (int j = start_y; j <= start_y + 30; j++)
        {
            mlx_pixel_put(mlx_data->mlx, mlx_data->mlx_win, i, j, color);
        }
    }
}

void player_position(t_mlx *mlx_data)
{
    char buffer[2];
    int byte = 0;
    int x = 0;
    int y = 0;
    mlx_data->fds.fd = open(mlx_data->fds.file_content, O_RDONLY);
    if (mlx_data->fds.fd == -1)
        exit(EXIT_FAILURE);
    while ((byte = read(mlx_data->fds.fd, buffer, 1)))
    {
        buffer[byte] = '\0';
        if (buffer[0] == 'P')
        {
            mlx_data->player.x = x * 30;
            mlx_data->player.y = y * 30;
        }
        x++;
        if (buffer[0] == '\n')
        {
            x = 0;
            y++;
        }
    }

    close(mlx_data->fds.fd);
}

void map(t_mlx *mlx_data)
{
    char buffer[2];
    int byte = 0;

    mlx_data->position.x = 0;
    mlx_data->position.y = 0;
    mlx_data->fds.fd = open(mlx_data->fds.file_content, O_RDONLY);
    if (mlx_data->fds.fd == -1)
        exit(EXIT_FAILURE);

    while ((byte = read(mlx_data->fds.fd, buffer, 1)))
    {
        buffer[byte] = '\0';
        if (buffer[0] == '1')
            drawing_square(mlx_data, 0x000000);
        else if (buffer[0] == '0')
            drawing_square(mlx_data, 0xFFFFFF);
        else if (buffer[0] == 'P')
            drawing_square(mlx_data, 0xFFFFFF);
        mlx_data->position.x += 30;
        if (buffer[0] == '\n')
        {
            mlx_data->position.x = 0;
            mlx_data->position.y += 30;
        }
    }
    close(mlx_data->fds.fd);
}