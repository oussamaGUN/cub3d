/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:07:56 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/14 23:49:58 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_count(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

int	invalid_char(char **split)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (split[++i])
	{
		j = 0;
		while (split[i][j] && split[i][j] != '\n')
		{
			if (!ft_isdigit(split[i][j]))
				return (0);
			j++;
		}
	}
	return (1);
}

int	how_many_commas(char *texture)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (texture[++i])
		if (texture[i] == ',')
			count++;
	if (count != 2)
		return (0);
	return (1);
}

int	check_rgb(char *texture)
{
	char	**split;

	if (!how_many_commas(texture))
		return (0);
	split = ft_split(texture, ',');
	if (!split)
	{
		printf("split faild");
		exit(1);
	}
	if (check_count(split) != 3 || ft_strcmp(split[2], "\n") == 0)
		return (free(split), 0);
	if (!invalid_char(split))
		return (free_split(split), 0);
	free_split(split);
	return (1);
}

int color_value(t_mlx *data, int flag)
{
    char    **split;
    int        i;

    i = 0;
    

    if (flag == 1)
    {
		split = ft_split(data->map_info.F, ',');
		if (!split)
		{
			printf("split faild");
			return (free_split(split), 0);
		}
		if (ft_atoi(split[0]) > 255 || ft_atoi(split[1]) > 255
        	|| ft_atoi(split[2]) > 255)
        	return (free_split(split), 0);
        data->floor.r = ft_atoi(split[0]);
        data->floor.g = ft_atoi(split[1]);
        data->floor.b = ft_atoi(split[2]);
		data->floor.color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
    }
    else
    {
		split = ft_split(data->map_info.C, ',');
		if (!split)
		{
			printf("split faild");
			return (free_split(split),0);
		}
		if (ft_atoi(split[0]) > 255 || ft_atoi(split[1]) > 255
        	|| ft_atoi(split[2]) > 255)
        	return (free_split(split), 0);
        data->ceil.r = ft_atoi(split[0]);
        data->ceil.g = ft_atoi(split[1]);
        data->ceil.b = ft_atoi(split[2]);
		data->ceil.color = (data->ceil.r << 16) | (data->ceil.g << 8) | data->ceil.b;   
    }

    return (free_split(split), 1);
}