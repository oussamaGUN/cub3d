/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:07:56 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/01 11:11:08 by ousabbar         ###   ########.fr       */
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
	if (check_count(split) != 3)
		return (free(split), 0);
	if (!invalid_char(split))
		return (free_split(split), 0);
	free_split(split);
	return (1);
}
