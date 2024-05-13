#include "main.h"


int	main(int ac, char *av[])
{
	t_mlx mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win_height = 666;
	mlx_data.mlx_win_width = 1000;
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, mlx_data.mlx_win_width, mlx_data.mlx_win_height, "Hello world!");
	// parser();
	ray_casting(&mlx_data, ac, av);
	mlx_loop(mlx_data.mlx);
}
