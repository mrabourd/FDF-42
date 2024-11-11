/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:15:08 by mrabourd          #+#    #+#             */
/*   Updated: 2023/02/28 12:03:11 by mrabourd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define WINDOW_WIDTH 1920	
# define WINDOW_HEIGHT 1280
# define SIN 0.85090352453
# define COS 0.52532198881

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_image
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_parallele
{
	double	x_start;
	double	y_start;
	double	x_delta;
	double	y_delta;
	double	x_px;
	double	y_px;
	int		center_x;
	int		center_y;
}				t_prll;

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_coord;

typedef struct s_iso
{
	double	space;
	int		center_x;
	int		center_y;
}				t_iso;

typedef struct s_tab
{
	int		width;
	int		height;
	int		height_z;
	int		upper;
	int		lower;
	char	*final;
	char	*str;
	char	**s;
	t_coord	**coord;
}				t_tab;

typedef struct s_line
{
	double	x_start;
	double	y_start;
	double	x_delta;
	double	y_delta;
	double	x_px;
	double	y_px;
}				t_line;

typedef struct s_zoom
{
	int	mouse_x;
	int	mouse_y;
}				t_zoom;

typedef struct s_struct
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		proj;
	t_image	img;
	t_tab	tab;
	t_line	line;
	t_iso	iso;
	t_prll	prll;
	t_zoom	zoom;
}				t_mlx;

/*MAIN*/
void	upper_lower(t_mlx *mlx);
void	define_place(t_mlx *mlx);
void	define_space(t_mlx *mlx);
void	fdf(t_mlx *mlx);

/*CREATE MAP*/
void	rm_space_atoi(t_tab *tab, char *str, int i);
void	rm_space(t_tab *tab);
int		nb_space(char *str);
int		ft_count_int(char *str);
void	create_tab(t_tab *tab, int fd);

/*MAP_UTILS*/
void	fill_index_tab(t_tab *tab);
void	check_error(t_tab *tab);

/*RENDER*/
void	render_background(t_image *img, int color);
void	render_proj(t_mlx *mlx, int x, int y);
void	render_map(t_mlx *mlx);
int		render(t_mlx *mlx);
void	img_pxl_put(t_image *img, int x, int y, int color);

/*DRAW LINE*/
int		x_iso_line(t_mlx *mlx, int x, int y);
int		y_iso_line(t_mlx *mlx, int x, int y, int z);
int		map_iso(t_mlx *mlx, t_coord start, t_coord end);
void	draw_line(t_mlx *mlx, t_coord start, t_coord end);

/*PARALLELE*/
int		x_prll(t_mlx *mlx, int x, int y);
int		y_prll(t_mlx *mlx, int x, int z);
int		map_prll(t_mlx *mlx, t_coord start, t_coord end);
void	draw_line_prll(t_mlx *mlx, t_coord start, t_coord end);

/*HOOKS*/
int		handle_keypress_colors2(int keysym, t_mlx *mlx, int color);
int		handle_keypress_colors(int keysym, t_mlx *mlx, int color);
int		handle_keypress_arrow(int keysym, t_mlx *mlx);
int		handle_keypress(int keysym, t_mlx *mlx);

/*MOUSE HOOK*/
int		handle_mouse(int button, int x, int y, t_mlx *mlx);

/*EXIT*/
void	free_tab(char **tab);
void	free_tab_int(t_tab *tab);
void	ft_exit_tab(t_tab *tab, int y);
int		ft_free_all(t_mlx *mlx);

/*ATOI*/
void	ft_atoi(char *nptr, int x, int y, t_tab *tab);

/*GNL*/

int		get_next_line(int fd, t_tab *tab);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_malloc(size_t len_new);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, int start, int len);
char	*fill_final(t_tab *tab, char *buf);
int		check_n(char *s);
char	*malloc_buf(int buf_s);

#endif