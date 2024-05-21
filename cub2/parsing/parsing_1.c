#include "../main.h"

void file_opennig(t_mlx *mlx_data)
{
    mlx_data->map_file.fd = open(mlx_data->map_file.av, O_RDONLY);
    if (mlx_data->map_file.fd == -1)
        printf("file error 1\n"), exit(1);
}
void parse_texture(char **texture, t_mlx *mlx_data)
{
    if (!ft_strcmp(texture[0], "NO\n") || !ft_strcmp(texture[0], "NO"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for NO\n"), exit(1);
        mlx_data->map_info.NO = ft_strdup(texture[1]);
    }
    else if (!ft_strcmp(texture[0], "SO\n") || !ft_strcmp(texture[0], "SO"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for SO\n"), exit(1);
        mlx_data->map_info.SO = ft_strdup(texture[1]);
    }
    else if (!ft_strcmp(texture[0], "WE\n") || !ft_strcmp(texture[0], "WE"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for WE\n"), exit(1);
        mlx_data->map_info.WE = ft_strdup(texture[1]);
    }
    else if (!ft_strcmp(texture[0], "EA\n") || !ft_strcmp(texture[0], "EA"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for EA\n"), exit(1);
        mlx_data->map_info.EA = ft_strdup(texture[1]);
    }
}
void parse_color(char **texture, t_mlx *mlx_data)
{
    if (!ft_strcmp(texture[0], "F\n") || !ft_strcmp(texture[0], "F"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for F\n"), exit(1);
        mlx_data->map_info.F = ft_strdup(texture[1]);
    }
    else if (!ft_strcmp(texture[0], "C\n") || !ft_strcmp(texture[0], "C"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for C\n"), exit(1);
        mlx_data->map_info.C = ft_strdup(texture[1]);
    }
}
void pars_line(t_mlx *mlx_data, char *line)
{
    char **texture;
    texture = ft_split(line, ' ');
    if (!texture)
        printf("Error\n"), exit(1);
    parse_texture(texture, mlx_data);
    parse_color(texture, mlx_data);
}
void file_reading(t_mlx *mlx_data)
{
    char *line = NULL;
    while (1)
    {
        line = get_next_line(mlx_data->map_file.fd);
        if (!line)
            break;
        pars_line(mlx_data, line);
    }
}
void parsing(t_mlx *mlx_data)
{
    file_opennig(mlx_data);
    file_reading(mlx_data);
    // printf("%s\n", mlx_data->map_info.EA);
}