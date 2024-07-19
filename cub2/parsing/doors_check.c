/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:35:18 by ousabbar          #+#    #+#             */
/*   Updated: 2024/07/19 17:08:02 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void doors_check(t_mlx *mlx_data)
{
    int i;
    int j;
    i = 0;
    while (mlx_data->map_info.map[i])
    {
        j = 0;
        while (mlx_data->map_info.map[i][j])
        {
            if (mlx_data->map_info.map[i][j] == 'D' 
            && ((mlx_data->map_info.map[i][j + 1] != '1' || mlx_data->map_info.map[i][j - 1] != '1')
                && (mlx_data->map_info.map[i + 1][j] != '1' || mlx_data->map_info.map[i - 1][j] != '1')))
            {
                ft_free_one(mlx_data, mlx_data->map_info.map[i], "Error");
                exit(0);
            }
            j++;
        }
        i++;
    }
}