/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:40:21 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/12 15:00:31 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;
	int		len;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	if (len == 0)
		return (NULL);
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (ft_strlen(s1) == 0)
		s1 = malloc_z();
	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	if (s2)
	{
		while (s2[y] != '\0')
			dst[i++] = s2[y++];
	}
	dst[i] = '\0';
	free(s1);
	free(s2);
	return (dst);
}

int	check_n(char *s)
{
	int		i;

	i = 1;
	if (!s)
		return (0);
	while (s && s[i - 1] != '\0')
	{
		if (s[i - 1] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (0);
}

char	*fill_final(t_tab *tab, char *tmp)
{
	int	i;

	i = 0;
	tab->final = malloc((check_n(tmp) + 1) * sizeof(char));
	if (tab->final == NULL)
		return (NULL);
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		tab->final[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		tab->final[i] = '\n';
		i++;
	}
	tab->final[i] = '\0';
	return (tab->final);
}

int	get_next_line(int fd, t_tab *tab)
{
	char		*buf;
	static char	*tmp = NULL;
	int			ret;

	ret = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	while (check_n(tmp) == 0 && ret > 0)
	{
		buf = malloc_buf(BUFFER_SIZE);
		ret = read(fd, buf, BUFFER_SIZE);
		tmp = ft_strjoin(tmp, buf);
	}
	if (check_n(tmp) != 0)
	{
		tab->final = fill_final(tab, tmp);
		tmp = ft_substr(tmp, check_n(tmp), ft_strlen(tmp) - check_n(tmp));
		return (1);
	}
	tab->final = ft_strdup(tmp);
	free(tmp);
	tmp = 0;
	return (0);
}
