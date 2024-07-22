/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:21:47 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/22 14:23:05 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	floor_color_value(t_mlx *data)
{
	char	**split;

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
	data->floor.color = (data->floor.r << 16)
		| (data->floor.g << 8) | data->floor.b;
	return (free_split(split), 1);
}

int	ceil_color_value(t_mlx *data)
{
	char	**split;

	split = ft_split(data->map_info.C, ',');
	if (!split)
	{
		printf("split faild");
		return (free_split(split), 0);
	}
	if (ft_atoi(split[0]) > 255 || ft_atoi(split[1]) > 255
		|| ft_atoi(split[2]) > 255)
		return (free_split(split), 0);
	data->ceil.r = ft_atoi(split[0]);
	data->ceil.g = ft_atoi(split[1]);
	data->ceil.b = ft_atoi(split[2]);
	data->ceil.color = (data->ceil.r << 16)
		| (data->ceil.g << 8) | data->ceil.b;
	return (free_split(split), 1);
}
