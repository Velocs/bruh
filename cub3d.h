/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:52:37 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/21 19:33:12 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdarg.h>
# include <fcntl.h>
# include "minilibX/mlx.h"
# include "get_next_line/get_next_line_bonus.h"

#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

typedef struct s_items
{
	void	*mlx;
	void	*win;
	float 	px, py, pdx, pdy, pa;
	void	*img;
	char	*addr;
	char	*map;
	char	**matrix;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		thickness;
	int		x;
	int		y;
	int		w;
	int		a;
	int		s;
	int		d;
	int		esc;
	int		x0;
	int		y0;
	int		ipx;
	int		ipx_add_x0;
	int		ipx_sub_x0;
	int		ipy;
	int		ipy_add_y0;
	int		ipy_sub_y0;
	int		x_max;
	int		y_max;
	// int		px;
	// int		py;
	// int		size_x;
	// int		size_y;
	// int		key;
	// char	*map;
	// char	**matrix;
}				t_items;


// void	initializer(t_items *it);
// void	fd_check(t_items *it);
void	matrix_c(t_items *it);
void	free_matrix(t_items *it);
// void	print_matrix(t_items *it);
// //void	draw_player(t_items *it);
// void	drawblack(t_items *it);
// int		ft_exit(t_items *it);
// int		ft_strcmp(char *s1, char *s2);
int		line_counter(t_items *it);
int		column_counter(t_items *it);
// int		check_input(int key, t_items *it);
// size_t	ft_strlen(const char *str);
#endif
