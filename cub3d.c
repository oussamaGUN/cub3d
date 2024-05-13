#include "main.h"


int	main(void)
{
	struct t_mlx mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win_height = 700;
	mlx_data.mlx_win_width = 500;
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, mlx_data.mlx_win_height, mlx_data.mlx_win_width, "Hello world!");
	// parser();
	ray_casting(&mlx_data);
	mlx_loop(mlx_data.mlx);
}
