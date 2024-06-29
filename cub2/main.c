#include "main.h"


int main(int ac, char const *av[])
{
    t_mlx mlx_data;
    if (ac != 2 || ft_check_extension((char *)av[1], ".cub") == 0)
        return (printf("invalid argument\n"), 1);
    mlx_data.map_file.av = ft_strdup(av[1]);
    parsing(&mlx_data);
    //raycasting();
    free(mlx_data.map_file.av);
    free_infos(&mlx_data);
    free(mlx_data.map_info.mapstr);
    free_split(mlx_data.map_info.map);
    return 0;
}
