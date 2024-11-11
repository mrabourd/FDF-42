/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:35:13 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/08 16:01:07 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char s, char const *set)
{
	int	i;

	i = 0;
	if (!set[i])
		return (0);
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*malloc_z(void)
{
	char	*s1;

	s1 = malloc(sizeof(char) * 1);
	if (s1 == 0)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len_s;
	char	*new;

	i = 0;
	while (s1[i])
		i++;
	len_s = i;
	i = 0;
	while (ft_ischarset(s1[i], set) && s1[i])
	{
		i++;
		if (i == len_s)
		{
			return (malloc_z());
		}
	}
	while (ft_ischarset(s1[len_s - 1], set))
		len_s--;
	new = malloc(sizeof(char) * (len_s - i + 1));
	if (new == 0)
		return (new);
	ft_strlcpy(new, &s1[i], (len_s - i + 1));
	return (new);
}
