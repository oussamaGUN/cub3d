#include "../main.h"

int check_count(char **split)
{
    int count = 0;
    while (split[count])
        count++;
    return count;
}
int invalid_char(char **split)
{
    int i = -1;
    int j = 0;
    while (split[++i])
    {
        j = 0;
        while (split[i][j] && split[i][j] != '\n')
        {
            if (!ft_isdigit(split[i][j]))
                return 0;
            j++;
        }
    }
    return 1;
}
int how_many_commas(char *texture)
{
    int i = -1;
    int count = 0;
    while (texture[++i])
        if (texture[i] == ',')
            count++;
    if (count != 2)
        return 0;
    return 1;
}
int ft_check_rgb(char *texture)
{
    if (!how_many_commas(texture))
        return 0;
    char **split = ft_split(texture, ',');
    if (!split)
        printf("split faild"), exit(1);
    if (check_count(split) != 3)
        return free(split),0;
    if (!invalid_char(split))
        return free_split(split),0;
    free_split(split);
    return 1; 
}
int parse_color(char **texture, t_mlx *mlx_data)
{
    if (!ft_strncmp(texture[0], "F", 1))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n") || !ft_check_rgb(texture[1]))
            return (printf("no texture for F "), 0);
        mlx_data->map_info.texture_number++;
        mlx_data->map_info.F = ft_strdup(texture[1]);
        return 1;
    }
    else if (!ft_strncmp(texture[0], "C", 2))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n") || !ft_check_rgb(texture[1]))
            return (printf("no texture for C "), 0);
        mlx_data->map_info.texture_number++;
        mlx_data->map_info.C = ft_strdup(texture[1]);
        return 1;
    }
    return 0;
}
int parse_texture(char **texture, t_mlx *mlx_data)
{
    if (!ft_strncmp(texture[0], "NO", 2))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            return (printf("no texture for NO "), 0);
        mlx_data->map_info.NO = ft_strdup(texture[1]);
        mlx_data->map_info.texture_number++;
        return 1;
    }
    if (!ft_strncmp(texture[0], "SO", 2))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            return (printf("no texture for SO "), 0);
        mlx_data->map_info.texture_number++;
        mlx_data->map_info.SO = ft_strdup(texture[1]);
        return 1;
    }
    if (!ft_strncmp(texture[0], "WE", 2))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            return (printf("no texture for WE "), 0);
        mlx_data->map_info.texture_number++;
        mlx_data->map_info.WE = ft_strdup(texture[1]);
        return 1;
    }
    if (!ft_strncmp(texture[0], "EA", 2))
    {
        if (!texture[1] || !ft_strcmp(texture[1], "\n"))
            return (printf("no texture for EA "), 0);
        mlx_data->map_info.texture_number++;
        mlx_data->map_info.EA = ft_strdup(texture[1]);
        return 1;
    }
    return 0;
}
void ft_free_one(t_mlx *mlx_data, char *line, char *parse_msg)
{
    printf("%s\n", parse_msg);
    free(line);
    free_infos(mlx_data);
    close(mlx_data->map_file.fd);
    free(mlx_data->map_file.av);
    exit(1);
}
void parse_line(t_mlx *mlx_data, char *line)
{
    if (!ft_strcmp(line, "\n"))
        return ;
    char **texture;
    texture = ft_split(line, ' ');
    if (!texture)
        ft_free_one(mlx_data, line, "split failed");
    if ((!parse_texture(texture, mlx_data) && !parse_color(texture, mlx_data)) || texture[2])
    {
        free_split(texture);
        ft_free_one(mlx_data, line, "invalid texture"); // get_next_line leak
    }
    free_split(texture);
}

int contain_one_only(char *texture)
{
    int i;
    i = -1;
    while (texture[++i])
        if (texture[i] != '1' || texture[i] != ' ' || texture[i] != '\n')
            return 0;
    return 1;
}
void reading_textures(t_mlx *mlx_data)
{
    mlx_data->map_info.line = NULL;
    mlx_data->map_info.texture_number = 0;
    while (1)
    {
        mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
        if (!mlx_data->map_info.line)
            break;
        if (mlx_data->map_info.texture_number == 6 && !contain_one_only(mlx_data->map_info.line))    
            break;
        parse_line(mlx_data, mlx_data->map_info.line);
        free(mlx_data->map_info.line);
    }
}
