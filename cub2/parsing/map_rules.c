#include "../main.h"

int map_height_width(t_mlx *mlx_data)
{
    int max = 0;
    mlx_data->map_info.height = 0;
    while (mlx_data->map_info.map[mlx_data->map_info.height])
    {
        int len = ft_strlen(mlx_data->map_info.map[mlx_data->map_info.height]);
        if (len >= max)
            max = len;
        mlx_data->map_info.height++;
    }
    if (mlx_data->map_info.height <= 2)
        printf("map is so small can't fit\n"), exit(1);
    return max;
}

void check_player(t_mlx *mlx_data)
{
    int count = 0;
    int x;
    int y;
    y = 0;
    while (y < mlx_data->map_info.height)
    {
        x = 0;
        while (mlx_data->map_info.map[y][x])
        {
            if (mlx_data->map_info.map[y][x] == 'N' || mlx_data->map_info.map[y][x] == 'W'
            || mlx_data->map_info.map[y][x] == 'S' || mlx_data->map_info.map[y][x] == 'E')
            {
                if ((mlx_data->map_info.map[y + 1][x] != '1' && mlx_data->map_info.map[y + 1][x] != '0')
                || (mlx_data->map_info.map[y - 1][x] != '1' && mlx_data->map_info.map[y - 1][x] != '0'))
                {
                    printf("invalid player postion\n");
                    free(mlx_data->map_info.mapstr);
                    free_split(mlx_data->map_info.map);
                    free_infos(mlx_data);
                    free(mlx_data->map_info.line);
                    close(mlx_data->map_file.fd);
                    free(mlx_data->map_file.av);
                    exit(1);
                }
                count++;
            }
            x++;
        }
        y++;
    }
    if (count != 1)
    {
        printf("invalid players count\n");
        free(mlx_data->map_info.mapstr);
        free_split(mlx_data->map_info.map);
        free_infos(mlx_data);
        free(mlx_data->map_info.line);
        close(mlx_data->map_file.fd);
        free(mlx_data->map_file.av);
        exit(1);
    }
}

void check_empty_blocks(t_mlx *mlx_data)
{
    int x = 0;
    int y = 1;
    while (mlx_data->map_info.map[y])
    {
        x = 0;
        while (mlx_data->map_info.map[y][x])
        {
            if (mlx_data->map_info.map[y][x] == '0')
            {
                if ((mlx_data->map_info.map[y + 1][x] != '1' && mlx_data->map_info.map[y + 1][x] != '0'
                    && mlx_data->map_info.map[y + 1][x] != 'N' && mlx_data->map_info.map[y + 1][x] != 'W'
                    && mlx_data->map_info.map[y + 1][x] != 'S' && mlx_data->map_info.map[y + 1][x] != 'E')
                    ||(mlx_data->map_info.map[y - 1][x] != '1' && mlx_data->map_info.map[y - 1][x] != '0'
                    && mlx_data->map_info.map[y - 1][x] != 'N' && mlx_data->map_info.map[y - 1][x] != 'W'
                    && mlx_data->map_info.map[y - 1][x] != 'S' && mlx_data->map_info.map[y - 1][x] != 'E'))
                    {
                        printf("map should be surrounded by walls\n");
                        free(mlx_data->map_info.mapstr);
                        free_split(mlx_data->map_info.map);
                        free_infos(mlx_data);
                        free(mlx_data->map_info.line);
                        close(mlx_data->map_file.fd);
                        free(mlx_data->map_file.av);
                        exit(1);
                    
                    }
            }
            x++;
        }
        y++;
    }
}
void surrounded_by_wall_check(t_mlx *mlx_data)
{
    mlx_data->vars.x = 0;
    mlx_data->vars.y = 0;

    int length;
    int i = 0;
    char **split;
    while (mlx_data->map_info.map[mlx_data->vars.y])
    {
        
        split = ft_split(mlx_data->map_info.map[mlx_data->vars.y], ' ');
        while (split[i])
        {
            mlx_data->vars.x = 0;
            while (split[i][mlx_data->vars.x])
            {
                length = ft_strlen(split[i]) - 1;
                if ((split[i][mlx_data->vars.x] == '0' || split[i][mlx_data->vars.x] == 'N' 
                    || split[i][mlx_data->vars.x] == 'S' || split[i][mlx_data->vars.x] == 'E' 
                    || split[i][mlx_data->vars.x] == 'W') && (mlx_data->vars.x == 0 || mlx_data->vars.y == 0 
                    || mlx_data->vars.x == length|| mlx_data->vars.y == mlx_data->map_info.height))
                {
                    printf("map should be surrounded walls\n");
                    free_split(split);
                    free(mlx_data->map_info.mapstr);
                    free_split(mlx_data->map_info.map);
                    free_infos(mlx_data);
                    free(mlx_data->map_info.line);
                    close(mlx_data->map_file.fd);
                    free(mlx_data->map_file.av);
                    exit(1);
                }
                mlx_data->vars.x++;
            }
            i++;
        }
        free_split(split);
        i = 0;
        mlx_data->vars.y++;
    }
}

void map_rules(t_mlx *mlx_data)
{
    mlx_data->map_info.map = ft_split(mlx_data->map_info.mapstr, '\n');
    if (!mlx_data->map_info.map)
    {
        printf("split fail\n");
        free(mlx_data->map_info.mapstr);
        free_infos(mlx_data);
        free(mlx_data->map_info.line);
        close(mlx_data->map_file.fd);
        free(mlx_data->map_file.av);
        exit(1);
    }
    mlx_data->map_info.height = ft_arrlen(mlx_data->map_info.map) - 1;
    mlx_data->map_info.width = map_height_width(mlx_data);
    surrounded_by_wall_check(mlx_data);
    check_empty_blocks(mlx_data);
    check_player(mlx_data);
}
