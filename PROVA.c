#include "minilibX/mlx.h"
#include <math.h>
#include "cub3d.h"
#include <stdio.h>

//-----------------------------MAP----------------------------------------------
#define mapX  8	  //map width
#define mapY  8	  //map height
#define mapS 64	  //map cube size
#define PI 3.14159
#define P2 PI/2
#define P3 3*PI/2
int map[] =		   //the map array. Edit to change level but keep the outer walls
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

// unsigned int	get_pixel(t_items *it, int x, int y)
// {
// 	char	*dest;

// 	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
// 		return (1);
// 	dest = it->addr + (y * it->line_length + x * (it->bits_per_pixel / 8));
// 	return (*(unsigned int *)dest);
// }

// static t_data *load(t_data *mlx, char *s)
// {
// 	t_data	*data;
// 	int		a;
// 	int		b;

// 	data = malloc(sizeof(t_data));
// 	a = 64;
// 	b = 64;
// 	data->img = mlx_png_file_to_image(mlx->mlx_ptr, s, &a, &b);
// 	if (data->img == NULL)
// 	{
// 		free(data);
// 		return (NULL);
// 	}
// 	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
// 			&data->line_length, &data->endian);
// 	return (data);
	
// }

// void	ft_create_level(t_data *mlx)
// {
// 	mlx->map->textures = malloc(sizeof(t_textures));
// 	mlx->map->textures->ea = load(mlx, "src/wall_ea.png");
// 	mlx->map->textures->no = load(mlx, "src/wall_no.png");
// 	mlx->map->textures->so = load(mlx, "src/wall_so.png");
// 	mlx->map->textures->we = load(mlx, "src/wall_we.png");
// 	mlx->map->color = 0x00FFFF;
// 	mlx->map->depth = (int *)malloc(sizeof(float) * 1200);
// 	ft_map_convert(mlx);
// 	ft_get_player_pos(mlx);
// 	mlx->map->pa = 90;
// 	mlx->map->pdx = cos(degtorad(mlx->map->pa));
// 	mlx->map->pdy = -sin(degtorad(mlx->map->pa));
// 	printf("player found at x: %f y: %f\n", mlx->map->px, mlx->map->py);
// 	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);

// }

void drawLine(void *mlx, void *win, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(mlx, win, x1, y1, color);

		if (x1 == x2 && y1 == y2)
			break;

		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}

		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	my_mlx_pixel_put(t_items *it, int x, int y, int color)
{
	char	*dst;

	dst = it->addr + (y * it->line_length + x * (it->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_exit(t_items *it)
{
	mlx_destroy_window(it->mlx, it->win);
	exit (0);
	return (0);
}
int FixAng(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return a;
}

float degToRad(int a)
{
	return a * M_PI / 180.0;
}

void	initializer(t_items *it)
{
	it->mlx = mlx_init();
	it->win = mlx_new_window(it->mlx, 1024, 512, "cub3d");
	it->img = mlx_new_image(it->mlx, 1024, 512);
	it->addr = mlx_get_data_addr(it->img, &it->bits_per_pixel, &it->line_length, &it->endian);
	it->px = 150;
	it->py = 400;
	it->pa = 90;
	it->pdx = cos(degToRad(it->pa));
	it->pdy = -sin(degToRad(it->pa));
	it->thickness = 8;
	it->ipx = 0;
	it->ipx_add_x0 = 0;
	it->ipx_sub_x0 = 0;
	it->ipy = 0;
	it->ipy_add_y0 = 0;
	it->ipy_sub_y0 = 0;
	it->x0 = 0;
	it->y0 = 0;

}

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );
}

void	draw3DWall(t_items *it, int r, float lineOff, float lineH)
{
    for (int y = lineOff; y < lineOff + lineH; y++)
    {
		for (int i = 0; i <= it->thickness; i++)
		{
        	int color = 0xFF0000; // Colore rosso per la barra
        	my_mlx_pixel_put(it, r * 8 + 514 + i, y, color);
    	}
	}
}

void	ft_clear(t_items *it)
{
	mlx_destroy_image(it->mlx, it->img);
	it->img = mlx_new_image(it->mlx, 1024, 512);
	it->addr = mlx_get_data_addr(it->img, &it->bits_per_pixel, &it->line_length, &it->endian);
}

void draw_rays_2d(t_items	*it)
{
    int r, mx, my, mp, dof;
    float vx, vy, rx, ry, ra, xo, yo, disT;

    ra = FixAng(it->pa + 30);
    for (r = 0; r < 60; r++)
    {
        dof = 0;
		float disV = 1000000;
        float Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)it->px / 64) * 64) + 64;
            ry = (it->px - rx) * Tan + it->py;
            xo = 64;
            yo = -xo * Tan;
        }
        else if (cos(degToRad(ra)) < -0.001)
        {
            rx = (((int)it->px / 64) * 64) - 0.0001;
            ry = (it->px - rx) * Tan + it->py;
            xo = -64;
            yo = -xo * Tan;
        }
        else
        {
            rx = it->px;
            ry = it->py;
            dof = 10;
        }
        while (dof < 10)
        {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            mp = my * it->x_max + mx;
            if (mp > 0 && mp < it->x_max * it->y_max && it->matrix[mp%it->y_max][mp/it->y_max] == '1')
			{
                dof = 10;
				disV = cos(degToRad(ra)) * (rx - it->px) -sin(degToRad(ra)) * (ry - it->py);
			}
			else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
		vx = rx;
		vy = ry;

		dof = 0;
		float disH = 1000000, hx = it->px, hy = it->py;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)it->py / 64) * 64) -0.0001;
            rx = (it->py - ry) * Tan + it->px;
            yo = -64;
            xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)it->py / 64) * 64) + 64;
            rx = (it->py - ry) * Tan + it->px;
            yo = 64;
            xo = -yo * Tan;
        }
        else
        {
            ry = it->py;
            rx = it->px;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            mp = my * it->y_max + mx;
            if (mp > 0 && mp < it->x_max * it->y_max && it->matrix[mp/it->x_max][mp%it->x_max] == '1')
			{
                dof = 8;
				hx = rx;
				hy = ry;
				disH = cos(degToRad(ra)) * (rx - it->px) - sin(degToRad(ra)) * (ry - it->py);
			}
			else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}

		float ca = it->pa-ra;
		if (ca < 0)
			 ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(degToRad(ca));
  		float lineH = (mapS * 320) / (disT);
		if (lineH > 320)
			lineH = 320;
  		float lineOff = 160 - lineH / 2;
		draw3DWall(it, r, lineOff, lineH);
		ra = FixAng(ra - 1);
    }
	mlx_put_image_to_window(it->mlx, it->win, it->img, 0, 0);
}

void drawMap2D(t_items *it)
{
	int x, y;
	for (y = 0; y < it->y_max; y++)
	{
		for (x = 0; x < it->x_max; x++)
		{
			if (map[y * it->x_max + x] == 1)
			{
				int startX = x * mapS;
				int startY = y * mapS;
				int endX = startX + mapS;
				int endY = startY + mapS;

				// Disegna un quadrato per il valore 1
				for (int i = startX; i < endX; i++)
				{
					for (int j = startY; j < endY; j++)
					{
						my_mlx_pixel_put(it, i, j, 0xFFFFFF);
					}
				}
			}
		}
	}
	mlx_put_image_to_window(it->mlx, it->win, it->img, 0, 0);

}

void drawPlayer2D(t_items *it)
{
	int	i;
	int	j;

	j = -5;
	while (j < 5)
	{
		i = -5;
		while (i < 5)
		{
			my_mlx_pixel_put(it, it->px + i, it->py + j, 0xFFFF00);
			i++;
		}
		j++;
	}
	my_mlx_pixel_put(it, it->px, it->py, 0xFFFF00);
	drawLine(it->mlx, it->win, it->px, it->py, it->px + it->pdx * 30, it->py + it->pdy * 30, 0xFFFF00);
}

int	button_down(int key, t_items *it)
{
	if (key == 'w')
		it->w = 1;
	if (key == 'a')
		it->a = 1;
	if (key == 's')
		it->s = 1;
	if (key == 'd')
		it->d = 1;
	if (key == 65307)
		it->esc = 1;
	return (0);
}

int	button_up(int key, t_items *it)
{
	if (key == 'w')
		it->w = 0;
	if (key == 'a')
		it->a = 0;
	if (key == 's')
		it->s = 0;
	if (key == 'd')
		it->d = 0;
	if (key == 65307)
		it->esc = 0;
	return (0);
}

int movement(t_items *it)
{
	it->x0 = 0;
	it->y0 = 0;
	if (it->pdx < 0)
		it->x0 = -20;
	else
		it->x0 = 20;
	if (it->pdy < 0)
		it->y0 = -20;
	else
		it->y0 = 20;
	it->ipx = it->px / 64.0;
	it->ipx_add_x0 = (it->px + it->x0) / 64.0;
	it->ipx_sub_x0 = (it->px - it->x0) / 64.0;
	it->ipy = it->py / 64.0;
	it->ipy_add_y0 = (it->py + it->y0) / 64.0;
	it->ipy_sub_y0 = (it->py - it->y0) / 64.0;
	if (it->w == 1)
	{
		if (map[it->ipy * mapX + it->ipx_add_x0] == 0)
			it->px += it->pdx * 0.5;
		if (map[it->ipy_add_y0 * mapX + it->ipx] == 0)
			it->py += it->pdy * 0.5;
	}
	if (it->a == 1)
	{
		it->pa += 1;
		it->pa = FixAng(it->pa);
		it->pdx = cos(degToRad(it->pa));
		it->pdy = -sin(degToRad(it->pa));
	}
	if (it->s == 1)
	{
		if (map[it->ipy * mapX + it->ipx_sub_x0] == 0)
			it->px -= it->pdx * 0.5;
		if (map[it->ipy_sub_y0 * mapX + it->ipx] == 0)
			it->py -= it->pdy * 0.5;
	}
	if (it->d == 1)
	{
		it->pa -= 1;
		it->pa = FixAng(it->pa);
		it->pdx = cos(degToRad(it->pa));
		it->pdy = -sin(degToRad(it->pa));
	}
	if (it->esc == 1)
		ft_exit(it);
	ft_clear(it);
	drawMap2D(it);
	drawPlayer2D(it);
	draw_rays_2d(it);
	return (0);
}

void	printmatrix(t_items *it)
{
	int i;
	int	j;

	i = 0;
	while (it->matrix[i])
	{
		j = 0;
		while (it->matrix[i][j])
		{
			printf("%c", it->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


int main(int ac, char **av)
{
	t_items it;

	if(ac == 2)
	{
		it.map = av[1];
		initializer(&it);
		it.y_max = line_counter(&it);
		it.x_max = column_counter(&it);
		matrix_c(&it);
		//printmatrix(&it);
		drawMap2D(&it);
		drawPlayer2D(&it);
		draw_rays_2d(&it);
		mlx_hook(it.win, 2, (1L << 0), button_down, &it);
		mlx_hook(it.win, 3, 1L << 1, button_up, &it);
		mlx_loop_hook(it.mlx, movement, &it);
		mlx_hook(it.win, 17, 1L << 16, ft_exit, &it);
		mlx_loop(it.mlx);
	}
	return (0);
}