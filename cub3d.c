#include "main.h"


int	main(void)
{
	t_mlx mlx_data;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx, 700, 500, "Hello world!");
	// parser();
	ray_casting(mlx_data);
	mlx_loop(mlx);
}
