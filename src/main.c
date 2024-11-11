/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:02:39 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/28 12:03:12 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	upper_lower(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	mlx->tab.upper = mlx->tab.coord[y][x].z;
	mlx->tab.lower = mlx->tab.coord[y][x].z;
	while (y < mlx->tab.height - 1)
	{
		x = 0;
		while (x < mlx->tab.width)
		{
			if (mlx->tab.upper < mlx->tab.coord[y][x].z)
				mlx->tab.upper = mlx->tab.coord[y][x].z;
			if (mlx->tab.lower >= mlx->tab.coord[y][x].z)
				mlx->tab.lower = mlx->tab.coord[y][x].z;
			x++;
		}
		y++;
	}
}

void	define_place(t_mlx *mlx)
{
	if (mlx->tab.upper > mlx->tab.width)
	{
		mlx->iso.center_x = WINDOW_WIDTH / 2;
		mlx->iso.center_y = WINDOW_HEIGHT / 2;
		mlx->prll.center_x = WINDOW_WIDTH / 5;
		mlx->prll.center_y = WINDOW_HEIGHT / 3 * 2;
	}
	else
	{
		mlx->iso.center_x = WINDOW_WIDTH / 2;
		mlx->iso.center_y = WINDOW_HEIGHT / 4;
		mlx->prll.center_x = WINDOW_WIDTH / 5;
		mlx->prll.center_y = WINDOW_HEIGHT / 5 * 3;
	}
}

void	define_space(t_mlx *mlx)
{
	int	height;
	int	width;
	int	z_height;

	upper_lower(mlx);
	height = WINDOW_HEIGHT / (mlx->tab.height - 1);
	width = WINDOW_WIDTH / mlx->tab.width;
	z_height = (mlx->tab.upper + mlx->tab.lower);
	if (z_height != 0)
		z_height = WINDOW_HEIGHT / (mlx->tab.upper + mlx->tab.lower);
	if (height > 0 && height < width && height < z_height)
		mlx->iso.space = height / 2;
	else if (width > 0 && height > width && width < z_height)
		mlx->iso.space = width / 2;
	else if (z_height > 0 && height > z_height && width > z_height)
		mlx->iso.space = z_height / 2;
	if (mlx->iso.space == 0 && height > 0)
		mlx->iso.space = height / 2;
	else if (mlx->iso.space == 0 && height < 0)
		mlx->iso.space = width / 2;
	define_place(mlx);
}

void	fdf(t_mlx *mlx)
{
	mlx->proj = 1;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return ;
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (mlx->win_ptr == NULL)
		return ;
	mlx->img.image = mlx_new_image(mlx->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.image,
			&mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
	define_space(mlx);
	if (mlx->win_ptr != NULL)
		render_map(mlx);
	mlx_loop_hook(mlx->mlx_ptr, &render, mlx);
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, ButtonPress, ButtonPressMask, &handle_mouse, mlx);
	mlx_hook(mlx->win_ptr, 2, 1, &handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, &ft_free_all, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	int		fd;

	if (argc != 2)
		exit(EXIT_FAILURE);
	ft_bzero(&mlx, sizeof(mlx));
	fd = open(argv[1], O_RDONLY);
	create_tab(&mlx.tab, fd);
	close(fd);
	fdf(&mlx);
	ft_free_all(&mlx);
	return (0);
}
