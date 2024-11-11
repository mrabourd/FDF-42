/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:44:53 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/27 16:47:23 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress_colors2(int keysym, t_mlx *mlx, int color)
{
	int	x;
	int	y;

	y = 0;
	if (keysym == XK_w)
		color = 0xFFFFFF;
	if (keysym == XK_g)
		color = 0xFFFF00;
	if (keysym == XK_w || keysym == XK_g)
	{
		while (y < mlx->tab.height - 1)
		{
			x = 0;
			while (x < mlx->tab.width)
			{
				mlx->tab.coord[y][x].color = color;
				x++;
			}
			y++;
		}
	}
	render_map(mlx);
	return (0);
}

int	handle_keypress_colors(int keysym, t_mlx *mlx, int color)
{
	int	x;
	int	y;

	y = 0;
	if (keysym == XK_b)
		color = 0x00FFFF;
	if (keysym == XK_r)
		color = 0xFF0000;
	if (keysym == XK_b || keysym == XK_r)
	{
		while (y < mlx->tab.height - 1)
		{
			x = 0;
			while (x < mlx->tab.width)
			{
				mlx->tab.coord[y][x].color = color;
				x++;
			}
			y++;
		}
	}
	render_map(mlx);
	handle_keypress_colors2(keysym, mlx, color);
	return (0);
}

int	handle_keypress_arrow(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Up)
	{
		mlx->iso.center_y -= 10;
		mlx->prll.center_y -= 10;
	}
	if (keysym == XK_Down)
	{
		mlx->iso.center_y += 10;
		mlx->prll.center_y += 10;
	}
	if (keysym == XK_Left)
	{
		mlx->iso.center_x -= 10;
		mlx->prll.center_x -= 10;
	}
	if (keysym == XK_Right)
	{
		mlx->iso.center_x += 10;
		mlx->prll.center_x += 10;
	}
	render_map(mlx);
	return (0);
}

int	handle_keypress(int keysym, t_mlx *mlx)
{
	int	color;

	color = 0;
	if (keysym == XK_Escape)
		ft_free_all(mlx);
	if (keysym == XK_z)
		define_space(mlx);
	if (keysym == XK_1)
		mlx->proj = 1;
	if (keysym == XK_2)
		mlx->proj = 2;
	render_map(mlx);
	handle_keypress_arrow(keysym, mlx);
	handle_keypress_colors(keysym, mlx, color);
	return (0);
}
