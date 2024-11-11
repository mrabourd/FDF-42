/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallele.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:59 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/25 15:28:23 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	x_prll(t_mlx *mlx, int x, int y)
{
	int	x_prll;

	x_prll = mlx->iso.space * (y + SIN * x) + mlx->prll.center_x;
	return (x_prll);
}

int	y_prll(t_mlx *mlx, int x, int z)
{
	int	y_prll;

	y_prll = mlx->iso.space * (-z + COS * -x) + mlx->prll.center_y;
	return (y_prll);
}

int	map_prll(t_mlx *mlx, t_coord start, t_coord end)
{
	int	pixels;

	mlx->prll.x_start = x_prll(mlx, start.x, start.y);
	mlx->prll.y_start = y_prll(mlx, start.x, start.z);
	mlx->prll.x_delta = x_prll(mlx, end.x, end.y) - mlx->prll.x_start;
	mlx->prll.y_delta = y_prll(mlx, end.x, end.z) - mlx->prll.y_start;
	pixels = sqrt((mlx->prll.x_delta * mlx->prll.x_delta)
			+ (mlx->prll.y_delta * mlx->prll. y_delta));
	mlx->prll.x_delta /= pixels;
	mlx->prll.y_delta /= pixels;
	mlx->prll.x_px = mlx->prll.x_start;
	mlx->prll.y_px = mlx->prll.y_start;
	return (pixels);
}

void	draw_line_prll(t_mlx *mlx, t_coord start, t_coord end)
{
	int	pixels;

	pixels = map_prll(mlx, start, end);
	while (pixels)
	{
		if ((mlx->prll.x_px < WINDOW_WIDTH && mlx->prll.x_px > 0)
			&& (mlx->prll.y_px < WINDOW_HEIGHT && mlx->prll.y_px > 0))
			img_pxl_put(&mlx->img, mlx->prll.x_px,
				mlx->prll.y_px, start.color);
		mlx->prll.x_px += mlx->prll.x_delta;
		mlx->prll.y_px += mlx->prll.y_delta;
		pixels--;
	}
}
