/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:41:18 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/25 18:22:22 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_background(t_image *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pxl_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	render_proj(t_mlx *mlx, int x, int y)
{
	if (mlx->proj == 1)
	{
		if (x + 1 < mlx->tab.width)
			draw_line(mlx, mlx->tab.coord[y][x],
				mlx->tab.coord[y][x + 1]);
		if (y + 1 < mlx->tab.height - 1)
			draw_line(mlx, mlx->tab.coord[y][x],
				mlx->tab.coord[y + 1][x]);
	}
	if (mlx->proj == 2)
	{
		if (x + 1 < mlx->tab.width)
			draw_line_prll(mlx, mlx->tab.coord[y][x], mlx->tab.coord[y][x + 1]);
		if (y + 1 < mlx->tab.height - 1)
			draw_line_prll(mlx, mlx->tab.coord[y][x], mlx->tab.coord[y + 1][x]);
	}
}

void	render_map(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	render_background(&mlx->img, 0x000000);
	while (y < mlx->tab.height - 1)
	{
		x = 0;
		while (x < mlx->tab.width)
		{
			if (mlx->proj == 1 || mlx->proj == 2)
				render_proj(mlx, x, y);
			x++;
		}
		y++;
	}
}

int	render(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.image, 0, 0);
	return (0);
}

void	img_pxl_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
		{
			*pixel++ = (color >> i) & 0xFF;
		}
		else
		{
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		}
		i -= 8;
	}
}
