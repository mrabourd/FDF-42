/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:53:57 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/25 18:25:51 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	nb_space(char *str)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

int	ft_count_int(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if ((((str[i]) >= '0' && str[i] <= '9')
				|| (str[i] >= 'A' && str[i] <= 'F')
				|| (str[i] >= 'a' && str[i] <= 'f')
				|| (str[i] == '-' || str[i] == '+'))
			&& (str[i + 1] == ' ' || str[i + 1] == '\n'
				|| str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

void	rm_space_atoi(t_tab *tab, char *str, int i)
{
	int		y;
	int		j;
	char	**tmp;

	y = 0;
	j = 0;
	if (!str)
		ft_exit_tab(tab, 1);
	tmp = ft_split(str, ' ');
	tab->coord[i] = malloc(sizeof(t_coord) * ft_count_int(str));
	if (!tab->coord)
	{
		free_tab(tmp);
		ft_exit_tab(tab, 1);
	}
	while (j < ft_count_int(str))
	{
		tab->coord[i][y].color = 0xFFFFFF;
		ft_atoi(tmp[j], i, y, tab);
		j++;
		y++;
	}
	free_tab(tmp);
}

void	rm_space(t_tab *tab)
{
	int		i;

	i = 0;
	tab->coord = malloc(sizeof(t_coord *) * (tab->height - 1));
	if (!tab->coord)
		ft_exit_tab(tab, 1);
	tab->width = ft_count_int(tab->s[i]);
	while (i < tab->height - 1)
	{
		rm_space_atoi(tab, tab->s[i], i);
		i++;
	}
	i = 0;
	while (i < tab->height - 1)
	{
		if (ft_count_int(tab->s[i]) != tab->width)
			ft_exit_tab(tab, 1);
		i++;
	}
}

void	create_tab(t_tab *tab, int fd)
{
	int		i;

	i = 1;
	while (i == 1)
	{
		i = get_next_line(fd, tab);
		tab->str = ft_strjoin(tab->str, tab->final);
		tab->height++;
	}
	check_error(tab);
	tab->s = ft_split(tab->str, '\n');
	if (tab->s == NULL)
		ft_exit_tab(tab, 1);
	if (tab->s[tab->height - 1] != NULL)
		tab->height += 1;
	rm_space(tab);
	fill_index_tab(tab);
}
