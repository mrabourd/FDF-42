/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:47:19 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/22 18:27:35 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	free_tab_int(t_tab *tab)
{
	int	i;

	i = 0;
	while (i < tab->height - 1)
	{
		if (tab->coord[i])
			free (tab->coord[i]);
		i++;
	}
	free (tab->coord);
}

void	ft_exit_tab(t_tab *tab, int y)
{
	if (tab->str)
		free (tab->str);
	if (tab->s)
		free_tab(tab->s);
	if (tab->coord)
		free_tab_int(tab);
	if (y == 1)
	{
		write (2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	ft_free_all(t_mlx *mlx)
{
	if (mlx->mlx_ptr)
	{
		render_background(&mlx->img, 0x000000);
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.image);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free (mlx->mlx_ptr);
	}
	ft_exit_tab(&mlx->tab, 0);
	return (1);
}
