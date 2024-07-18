/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:03:55 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/18 15:35:51 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	file_opennig(t_mlx *mlx_data)
{
	mlx_data->map_file.fd = open(mlx_data->map_file.av, O_RDONLY);
	if (mlx_data->map_file.fd == -1)
	{
		printf("file not found\n");
		free(mlx_data->map_file.av);
		exit(1);
	}
}

void	vars_init(t_mlx *mlx_data)
{
	mlx_data->map_info.C = NULL;
	mlx_data->map_info.F = NULL;
	mlx_data->map_info.EA = NULL;
	mlx_data->map_info.NO = NULL;
	mlx_data->map_info.SO = NULL;
	mlx_data->map_info.WE = NULL;
	mlx_data->map_info.map_index = 0;
}

int	ft_check_extension(char *str, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(ext) - 1;
	while (i >= 0 && j >= 0)
	{
		if (str[i] != ext[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

void	reading_textures(t_mlx *mlx_data)
{
	mlx_data->map_info.line = NULL;
	mlx_data->map_info.texture_number = 0;
	while (1)
	{
		mlx_data->map_info.line = get_next_line(mlx_data->map_file.fd);
		if (!mlx_data->map_info.line)
			break ;
		if (mlx_data->map_info.texture_number == 6
			&& !contain_one_only(mlx_data->map_info.line))
			break ;
		parse_line(mlx_data, mlx_data->map_info.line);
		free(mlx_data->map_info.line);
	}
}
void check_player_direction(t_mlx *mlx_data)
{
    int i;
    int j;

    j = 0;
    while (mlx_data->map_info.map[j])
    {
        i = 0;
        while (mlx_data->map_info.map[j][i])
        {
            if (mlx_data->map_info.map[j][i] == 'N')
                mlx_data->map_info.direction = (3. * M_PI) / 2.;
            else if (mlx_data->map_info.map[j][i] == 'W')
                mlx_data->map_info.direction = M_PI;
            else if (mlx_data->map_info.map[j][i] == 'S')
                mlx_data->map_info.direction = M_PI / 2.;
            else if (mlx_data->map_info.map[j][i] == 'E')
                mlx_data->map_info.direction = 0;
            i++;
        }
        j++;
    }
    printf("%f\n", mlx_data->map_info.direction);
}

void	parsing(t_mlx *mlx_data)
{
	vars_init(mlx_data);
	file_opennig(mlx_data);
	reading_textures(mlx_data);
	parsing_map(mlx_data);
	check_player_direction(mlx_data);
	texture_init(mlx_data);
	close(mlx_data->map_file.fd);
}
