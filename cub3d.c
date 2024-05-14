#include "main.h"


int	key_hook(int keycode, t_mlx *mlx_data)
{
	if (keycode == UP)
	{

	}
	else if (keycode == DOWN)
		printf("down\n");
	else if (keycode == LEFT)
		printf("left\n");
	else if (keycode == RIGHT)
		printf("right\n");
	return (0);
}
int	main(int ac, char *av[])
{
	t_mlx mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win_height = 666;
	mlx_data.mlx_win_width = 1000;
	mlx_data.movement.x_movement = 0;
	mlx_data.movement.y_movement = 0;
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, mlx_data.mlx_win_width, mlx_data.mlx_win_height, "Hello world!");
	// parser();
	ray_casting(&mlx_data, ac, av);
	mlx_key_hook(mlx_data.mlx_win, key_hook, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
