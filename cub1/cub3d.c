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
int compare_coor(int x,int y, t_wall *mlx_data)
{
	char map[ft_strlen_height(av[1])][ft_strlen_width(av[1])] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '0', 'P', '0', '0', '0', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	t_wall *itter = mlx_data->wall_coordinates;
    while (itter) {
		if (x > )
        itter = itter->next;
    }
	return 1;
}
int key_hook(int keycode, t_mlx *mlx_data) {
    int new_x = mlx_data->player.x;
    int new_y = mlx_data->player.y;

    if (keycode == UP) {
        new_y -= PLAYER_SPEED;
        if (!compare_coor(new_x, new_y, mlx_data))
            return 0;
        mlx_data->player.y -= PLAYER_SPEED;
    } else if (keycode == DOWN) {
        new_y += PLAYER_SPEED;
        if (!compare_coor(new_x, new_y, mlx_data))
            return 0;
        mlx_data->player.y += PLAYER_SPEED;
    } else if (keycode == LEFT) {
        new_x -= PLAYER_SPEED;
        if (!compare_coor(new_x, new_y, mlx_data))
            return 0;
        mlx_data->player.x -= PLAYER_SPEED;
    } else if (keycode == RIGHT) {
        new_x += PLAYER_SPEED;
        if (!compare_coor(new_x, new_y, mlx_data))
            return 0;
        mlx_data->player.x += PLAYER_SPEED;
    }

    draw(mlx_data);
    return (0);
}
void draw(t_mlx *mlx_data)
{
	mlx_clear_window(mlx_data->mlx, mlx_data->mlx_win);
	map(mlx_data);
	updating_position(mlx_data,  0xFF5733);
}
void add_node(t_wall **wall_coordinates, t_wall *wall)
{
	if (wall_coordinates)
	{
		if (*wall_coordinates)
			wall->next = *wall_coordinates;
		*wall_coordinates = wall;
	}
}
void wall_coordinates(t_mlx *mlx_data)
{
	mlx_data->fds.fd = open(mlx_data->fds.file_name, O_RDONLY);
	if (mlx_data->fds.fd == -1)
		exit(1);
	mlx_data->wall_coordinates = NULL;
	int x = 0;
	int y = 0;
	int byts;
	char buffer[2];
	while ((byts = read(mlx_data->fds.fd, buffer, 1)))
	{
		buffer[byts] = '\0';
		if (buffer[0] == '1')
		{
			t_wall *wall = malloc(sizeof(t_wall));
			wall->next = NULL;
			wall->x = x * 30;
			wall->y = y * 30;
			add_node(&mlx_data->wall_coordinates, wall);
		}
		x++;
		if (buffer[0] == '\n')
		{
			x = 0;
			y++;
		}
	}
}
int	main(int ac, char *av[])
{
	t_mlx mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.movement.x_movement = 0;
	mlx_data.movement.y_movement = 0;
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, ft_strlen_width(av[1]) * 30, ft_strlen_height(av[1]) * 30, "Hello world!");
	mlx_data.fds.file_name = ft_strdup(av[1]);
	wall_coordinates(&mlx_data);
	map(&mlx_data);
	player_position(&mlx_data);
	updating_position(&mlx_data,  0xFF5733);
	// mlx_hook(mlx_data.mlx_win, key_hook, &mlx_data);
		mlx_hook(mlx_data.mlx, 02, 0, key_hook, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
