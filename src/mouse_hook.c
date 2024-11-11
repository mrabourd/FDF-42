/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:44:58 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/28 12:03:09 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		mlx->iso.space *= 1.5;
	}
	if (button == 5)
	{
		if (mlx->iso.space < 1)
		{
			mlx->iso.space = 1;
		}
		if (mlx->iso.space >= 1)
		{
			mlx->iso.space /= 1.5;
		}
	}
	render_map(mlx);
	return (0);
}
