/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:54:02 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/16 19:55:27 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_error(t_tab *tab)
{
	int	i;

	i = 0;
	if (!tab->str || tab->str[i] == '\0')
		ft_exit_tab(tab, 1);
	while (tab->str[i] != '\0')
	{
		if (tab->str[i] == '\n')
		{
			if (tab->str[i + 1] && tab->str[i + 1] == '\n')
				ft_exit_tab(tab, 1);
			while (tab->str[i] && tab->str[i] == ' ')
			{
				if (tab->str[i] == '\n')
				{
					ft_exit_tab(tab, 1);
				}
				i++;
			}
		}
		i++;
	}
}

void	fill_index_tab(t_tab *tab)
{
	int	x;
	int	y;

	y = 0;
	while (y < tab->height - 1)
	{
		x = 0;
		while (x < tab->width)
		{
			tab->coord[y][x].x = x;
			tab->coord[y][x].y = y;
			x++;
		}
		y++;
	}
}
