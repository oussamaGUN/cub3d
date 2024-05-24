#include "../main.h"

void file_opennig(t_mlx *mlx_data)
{
    mlx_data->map_file.fd = open(mlx_data->map_file.av, O_RDONLY);
    if (mlx_data->map_file.fd == -1)
        printf("file error 1\n"), exit(1);
}
int parse_texture(char **texture, t_mlx *mlx_data)
{
    if (!ft_strcmp(texture[0], "NO\n") || !ft_strcmp(texture[0], "NO"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for NO\n"), exit(1);
        mlx_data->map_info.NO = ft_strdup(texture[1]);
        mlx_data->map_info.map_index++;
        return 1;
    }
    else if (!ft_strcmp(texture[0], "SO\n") || !ft_strcmp(texture[0], "SO"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for SO\n"), exit(1);
        mlx_data->map_info.map_index++;
        mlx_data->map_info.SO = ft_strdup(texture[1]);
        return 1;
    }
    else if (!ft_strcmp(texture[0], "WE\n") || !ft_strcmp(texture[0], "WE"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for WE\n"), exit(1);
        mlx_data->map_info.map_index++;
        mlx_data->map_info.WE = ft_strdup(texture[1]);
        return 1;
    }
    else if (!ft_strcmp(texture[0], "EA\n") || !ft_strcmp(texture[0], "EA"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for EA\n"), exit(1);
        mlx_data->map_info.map_index++;
        mlx_data->map_info.EA = ft_strdup(texture[1]);
        return 1;
    }
    return 0;
}
int parse_color(char **texture, t_mlx *mlx_data)
{
    if (!ft_strcmp(texture[0], "F\n") || !ft_strcmp(texture[0], "F"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for F\n"), exit(1);
        mlx_data->map_info.map_index++;
        mlx_data->map_info.F = ft_strdup(texture[1]);
        return 1;
    }
    else if (!ft_strcmp(texture[0], "C\n") || !ft_strcmp(texture[0], "C"))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            printf("no texture for C\n"), exit(1);
        mlx_data->map_info.map_index++;
        mlx_data->map_info.C = ft_strdup(texture[1]);
        return 1;
    }
    return 0;
}
int contain_one_only(char *texture)
{
    int i;
    i = -1;
    while (texture[++i])
        if (texture[i] != '1' || texture[i] != ' ')
            return 0;
    return 1;
}
void parse_map(t_mlx *mlx_data, char *line, char **texture)
{
    // if (!digit_check(texture[0]))
    //     return ;

    mlx_data->map_info.map[mlx_data->map_info.map_index] = ft_strdup(line);
    mlx_data->map_info.map_index++;
}
void parse_line(t_mlx *mlx_data, char *line)
{
    char **texture;
    texture = ft_split(line, ' ');
    if (!texture || texture[2] || !ft_strcmp(texture[2], "\n"))
        printf("Error\n"), exit(1);
    if (!parse_texture(texture, mlx_data) && !parse_color(texture, mlx_data)
        && ft_strcmp(texture[0], "\n"))
        printf("Error\n"),exit(1);
}
void reading_textures(t_mlx *mlx_data)
{
    mlx_data->map_info.line = NULL;
    mlx_data->map_info.map_index = 0;
    while (1)
    {
        mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
        if (!mlx_data->map_info.line)
            break;
        if (mlx_data->map_info.map_index == 6 && !contain_one_only(mlx_data->map_info.line))
            break;
        parse_line(mlx_data, mlx_data->map_info.line);
    }
    if (!mlx_data->map_info.C || !mlx_data->map_info.F
        || !mlx_data->map_info.EA || !mlx_data->map_info.NO 
        || !mlx_data->map_info.SO || !mlx_data->map_info.WE)
        printf("na9ss\n"), exit(1);
}
void vars_init(t_mlx *mlx_data)
{
    mlx_data->map_info.C = NULL;
    mlx_data->map_info.F = NULL;
    mlx_data->map_info.EA = NULL;
    mlx_data->map_info.NO = NULL;
    mlx_data->map_info.SO = NULL;
    mlx_data->map_info.WE = NULL;
    mlx_data->map_info.map_index = 0;
}
int line_rules(t_mlx *mlx_data)
{
    int i;
    i = -1;
    while (mlx_data->map_info.line[++i])
        if (mlx_data->map_info.line[i] != '1' && mlx_data->map_info.line[i] != '0'
            && mlx_data->map_info.line[i] != 'S' && mlx_data->map_info.line[i] != 'N'
            && mlx_data->map_info.line[i] != 'E' && mlx_data->map_info.line[i] != 'W'
            && mlx_data->map_info.line[i] != '\n' && mlx_data->map_info.line[i] != ' ')
            return 0;
    mlx_data->map_info.map[mlx_data->map_info.map_index] = ft_strdup(mlx_data->map_info.line);
    mlx_data->map_info.map_index++;
    return 1;
}
void check_errors(t_mlx *mlx_data)
{
    int i;
    if (!line_rules(mlx_data))
    {
        i = 0;
        while (i < mlx_data->map_info.map_index)
            free(mlx_data->map_info.map[i++]);
        free(mlx_data->map_info.map);
        printf("Error\n"), exit(1);
    }
}
int ft_arrlen(char **map)
{
    int i;
    i = 0;
    while (map[i])
        i++;
    return i;
}
void new_map(t_mlx *mlx_data)
{
    int arr_len = ft_arrlen(mlx_data->map_info.map) - 1;
    while (arr_len >= 0)
    {
        if (ft_strcmp(mlx_data->map_info.map[arr_len], "\n"))
            break ;
        mlx_data->map_info.map[arr_len] = NULL;
        arr_len--;
    }
}
void map_rules(t_mlx *mlx_data)
{
    new_map(mlx_data);
    for (size_t i = 0; mlx_data->map_info.map[i]; i++)
    {
        printf("%s",mlx_data->map_info.map[i]);
    }
    
}
void parsing_map(t_mlx *mlx_data)
{
    mlx_data->map_info.map = malloc(sizeof(char *) * 100);
    if (!mlx_data->map_info.map)
        printf("malloc fail\n"), exit(1);
    mlx_data->map_info.map_index = 0;
    while (!ft_strcmp(mlx_data->map_info.line, "\n"))
        mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
    while (1)
    {
        check_errors(mlx_data);
        mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
        if (!mlx_data->map_info.line)
            break;
    }
    mlx_data->map_info.map[mlx_data->map_info.map_index] = NULL;
    map_rules(mlx_data);
    
}
void parsing(t_mlx *mlx_data)
{
    vars_init(mlx_data);
    file_opennig(mlx_data);
    reading_textures(mlx_data);
    parsing_map(mlx_data);
}