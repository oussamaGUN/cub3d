/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:06:37 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/01 11:15:05 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_arrlen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_infos(t_mlx *mlx_data)
{
	free(mlx_data->map_info.C);
	free(mlx_data->map_info.F);
	free(mlx_data->map_info.SO);
	free(mlx_data->map_info.NO);
	free(mlx_data->map_info.WE);
	free(mlx_data->map_info.EA);
}

void	ft_free_one(t_mlx *mlx_data, char *line, char *parse_msg)
{
	printf("%s\n", parse_msg);
	free(line);
	free_infos(mlx_data);
	close(mlx_data->map_file.fd);
	free(mlx_data->map_file.av);
	exit(1);
}

int	contain_one_only(char *texture)
{
	int	i;

	i = -1;
	while (texture[++i])
		if (texture[i] != '1' || texture[i] != ' ' || texture[i] != '\n')
			return (0);
	return (1);
}
