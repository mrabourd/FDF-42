/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:36:04 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/08 16:01:37 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*new;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (len == 0)
	{
		free(s);
		return (NULL);
	}
	if (ft_strlen(s) < start)
		return (malloc_z());
	new = malloc(sizeof(char) * (len + 1));
	if (new == 0)
		return (NULL);
	while (len-- > 0)
	{
		new[i] = s[i + start];
		i++;
	}
	free(s);
	new[i] = '\0';
	return (new);
}

char	*malloc_buf(int buf_s)
{
	char	*s1;

	s1 = malloc(sizeof(char) * (buf_s + 1));
	if (s1 == 0)
		return (NULL);
	ft_bzero(s1, (buf_s + 1));
	return (s1);
}
