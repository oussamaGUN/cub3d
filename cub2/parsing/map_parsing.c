#include "../main.h"

int line_rules(t_mlx *mlx_data)
{
    int i;
    i = -1;
    while (mlx_data->map_info.line[++i])
    {
        if (mlx_data->map_info.line[i] != '1' && mlx_data->map_info.line[i] != '0'
            && mlx_data->map_info.line[i] != 'S' && mlx_data->map_info.line[i] != 'N'
            && mlx_data->map_info.line[i] != 'E' && mlx_data->map_info.line[i] != 'W'
            && mlx_data->map_info.line[i] != '\n' && mlx_data->map_info.line[i] != ' ')
            return 0;
    }
    mlx_data->map_info.mapstr = ft_strjoin(mlx_data->map_info.mapstr, mlx_data->map_info.line);
    return 1;
}

void check_errors(t_mlx *mlx_data)
{
    if (!line_rules(mlx_data))
    {
        printf("invalid character\n");
        free(mlx_data->map_info.mapstr);
        free_infos(mlx_data);
        free(mlx_data->map_info.line);
        close(mlx_data->map_file.fd);
        free(mlx_data->map_file.av);
        exit(1);
    }
}
void parsing_map(t_mlx *mlx_data)
{
    mlx_data->map_info.map_index = 0;
    mlx_data->map_info.mapstr = NULL;
    while (!ft_strcmp(mlx_data->map_info.line, "\n"))
    {
        free(mlx_data->map_info.line);
        mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
    }
    if (!mlx_data->map_info.line)
    {
        free_infos(mlx_data);
        printf("there is no map\n"), exit(1);
    }
    while (1)
    {
        check_errors(mlx_data);
        free(mlx_data->map_info.line);
        mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
        if (!mlx_data->map_info.line)
            break;
    } 
    map_rules(mlx_data);
}