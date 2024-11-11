/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:35:48 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/20 15:51:42 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	len_hex(char *hex)
{
	int		i;

	i = 0;
	while (hex[i])
		i++;
	return (i);
}

int	fill_color(int i, int res)
{
	while (i < 9)
	{
		res += 0 * pow(16, 9 - i - 1);
		i++;
	}
	return (res);
}

int	hex_to_int(t_tab *tab, char *hex)
{
	int	i;
	int	res;
	int	val;

	if (hex[1] != '0' || hex[2] != 'x')
		ft_exit_tab(tab, 1);
	i = 3;
	res = 0;
	val = 0;
	while (i < len_hex(hex))
	{
		if (hex[i] == '\0' || !hex[i])
			val = 0;
		if (hex[i] >= '0' && hex[i] <= '9')
			val = hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			val = hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			val = hex[i] - 'A' + 10;
		res += val * pow(16, 9 - i - 1);
		i++;
	}
	if (len_hex(hex) < 9)
		fill_color(i, res);
	return (res);
}

void	ft_atoi(char *nptr, int x, int y, t_tab *tab)
{
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	tab->coord[x][y].z = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{	
		if (nptr[i] == '-')
			signe = -signe;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		tab->coord[x][y].z = (tab->coord[x][y].z * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == ',')
	{
		tab->coord[x][y].color = hex_to_int(tab, &nptr[i]);
	}
	tab->coord[x][y].z = tab->coord[x][y].z * signe;
}
