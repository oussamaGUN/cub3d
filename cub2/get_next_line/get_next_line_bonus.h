/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ousabbar <ousabbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:47:22 by ousabbar          #+#    #+#             */
/*   Updated: 2024/05/21 16:18:59 by ousabbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#  define BUFFER_SIZE 42

# include "../main.h"

void	*ft_memmove(void *dest, const void *src, size_t n);
char	*get_next_line(int fd);
char	*ft_strchr_2(char *s, char c);
char	*ft_strjoin_2(char *s1, char *s2);
size_t	ft_strlen_2(char *s);
char	*ft_strdup(const char *s);

#endif
