#include "main.h"


int ft_strlen_width(char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(1);
    char buffer[10];
    int byte;
	int i = 0;
    while ((byte = read(fd, buffer, 1)))
    {
        buffer[byte] = '\0';
        if (buffer[0] == '\n')
			break;
		i++;
    }
	return i;
}
int ft_strlen_height(char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(1);
    char buffer[10];
    int byte;
	int i = 0;
    while ((byte = read(fd, buffer, 1)))
    {
        buffer[byte] = '\0';
        if (buffer[0] == '\n')
			i++;
    }
	return i + 1;
}
void updating_position(t_mlx *mlx_data, int color)
{
    int start_x = mlx_data->player.x;
    int start_y = mlx_data->player.y;
    for (int i = start_x; i <= start_x + 30; i++)
    {
        for (int j = start_y; j <= start_y + 30; j++)
        {
            mlx_pixel_put(mlx_data->mlx, mlx_data->mlx_win, i, j, color);
        }
    }
}
int	key_hook(int keycode, t_mlx *mlx_data)
{
	if (keycode == UP)
		mlx_data->player.y -= PLAYER_SPEED;
	else if (keycode == DOWN)
		mlx_data->player.y += PLAYER_SPEED;
	else if (keycode == LEFT)
		mlx_data->player.x -= PLAYER_SPEED;
	else if (keycode == RIGHT)
		mlx_data->player.x += PLAYER_SPEED;
	draw(mlx_data);
	return (0);
}
void draw(t_mlx *mlx_data)
{
	mlx_clear_window(mlx_data->mlx, mlx_data->mlx_win);
	map(mlx_data);
	updating_position(mlx_data,  0xFF5733);
}
int	main(int ac, char *av[])
{
	t_mlx mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.movement.x_movement = 0;
	mlx_data.movement.y_movement = 0;
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, ft_strlen_width(av[1]) * 30, ft_strlen_height(av[1]) * 30, "Hello world!");
	// parser();
	// mlx_data.position.x = 0;
    // mlx_data.position.y = 0;
	mlx_data.fds.file_content = ft_strdup(av[1]);
	map(&mlx_data);
	player_position(&mlx_data);
	updating_position(&mlx_data,  0xFF5733);
	mlx_key_hook(mlx_data.mlx_win, key_hook, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
