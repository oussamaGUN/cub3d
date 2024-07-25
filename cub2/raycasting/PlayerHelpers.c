/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlayerHelpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:17:12 by afadouac          #+#    #+#             */
/*   Updated: 2024/07/25 16:40:48 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	IsPlayer(char c)
{
	if (c == 'N' || c == 'S' \
		|| c == 'E' || c == 'W')
	{
		return (1);
	}
	return (0);
}

t_cordonate	GetPlayerPosition(char **map)
{
	t_cordonate	pos;
	int			i;
	int			j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (IsPlayer(map[i][j]))
			{
				pos.x = (j * SCALE) + 2;
				pos.y = (i * SCALE) + 2;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}
