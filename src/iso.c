/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:48:59 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/25 13:59:38 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	x_iso_line(t_mlx *mlx, int x, int y)
{
	int	x_iso;

	x_iso = mlx->iso.space * ((x - y) * SIN) + mlx->iso.center_x;
	return (x_iso);
}

int	y_iso_line(t_mlx *mlx, int x, int y, int z)
{
	int	y_iso;	

	y_iso = mlx->iso.space * ((x + y) * COS - z) + mlx->iso.center_y;
	return (y_iso);
}

int	map_iso(t_mlx *mlx, t_coord start, t_coord end)
{
	int	pixels;

	mlx->line.x_start = x_iso_line(mlx, start.x, start.y);
	mlx->line.y_start = y_iso_line(mlx, start.x, start.y, start.z);
	mlx->line.x_delta = x_iso_line(mlx, end.x, end.y) - mlx->line.x_start;
	mlx->line.y_delta = y_iso_line(mlx, end.x, end.y, end.z)
		- mlx->line.y_start;
	pixels = sqrt((mlx->line.x_delta * mlx->line.x_delta)
			+ (mlx->line.y_delta * mlx->line. y_delta));
	mlx->line.x_delta /= pixels;
	mlx->line.y_delta /= pixels;
	mlx->line.x_px = mlx->line.x_start;
	mlx->line.y_px = mlx->line.y_start;
	return (pixels);
}

void	draw_line(t_mlx *mlx, t_coord start, t_coord end)
{
	int	pixels;

	pixels = map_iso(mlx, start, end);
	while (pixels)
	{
		if ((mlx->line.x_px < WINDOW_WIDTH && mlx->line.x_px > 0)
			&& (mlx->line.y_px < WINDOW_HEIGHT && mlx->line.y_px > 0))
			img_pxl_put(&mlx->img, mlx->line.x_px, mlx->line.y_px, start.color);
		mlx->line.x_px += mlx->line.x_delta;
		mlx->line.y_px += mlx->line.y_delta;
		pixels--;
	}
}
