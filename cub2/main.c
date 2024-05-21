#include "main.h"


int main(int ac, char const *av[])
{
    t_mlx mlx_data;
    mlx_data.map_file.av = ft_strdup(av[1]);
    parsing(&mlx_data);
    return 0;
}
