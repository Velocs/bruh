/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:00:37 by lbusi             #+#    #+#             */
/*   Updated: 2023/11/21 17:41:26 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	matrix_c(t_items *it)
{
	int		fd;
	int		i;

	i = it->y_max;
	it->y = 0;
	fd = open(it->map, O_RDONLY);
	if (fd == -1)
		exit(0);
	it->matrix = (char **) malloc (sizeof(char *) * (i) + 1);
	if (!it->matrix)
		return ;
	while (i != 0)
	{
		it->matrix[it->y] = get_next_line(fd);
		it->y++;
		i--;
	}
	close(fd);
	it->matrix[it->y] = NULL;
}

void	free_matrix(t_items *it)
{
	int	i;

	i = 0;
	while (it->matrix[i])
	{
		free(it->matrix[i]);
		i++;
	}
}

int	line_counter(t_items *it)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(it->map, O_RDONLY);
	if (fd < 1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

int	column_counter(t_items *it)
{
	int		i;
	int		fd;
	char	*map;

	i = 0;
	fd = open(it->map, O_RDONLY);
	if (fd < 1)
		return (0);
	map = get_next_line(fd);
	while (map[i])
		i++;
	close(fd);
	free(map);
	return (i);
}