/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:05 by fde-jesu          #+#    #+#             */
/*   Updated: 2025/03/17 04:13:47 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"
#include "../libs/mlx/mlx.h"


void start_cub(t_cub *cub);
void init_cub(t_cub *cub);
void exit_msg(t_cub *cub, char *str);
void put_square(t_cub *cub, int x, int y, int size, int color);
int key_press(int kcode, t_cub *cub);
void close_window(void);
void move_player(t_cub *cub);
int  draw_loop(t_cub *cub);
void clear_win(t_cub *cub);
char **get_map(void);
void draw_map(t_cub *game);
void draw_line(t_cub *cub, float start_x, int i);



void close_window(void)
{
	exit(0);
}

void init_cub(t_cub *cub)
{

	cub->px = WIDTH / 2;//(WIDTH) /2 ;
	cub->py = HEIGH / 2;//(HEIGH) /2;

	cub->k_up = false;
    cub->k_down = false;
    cub->k_left = false;
    cub->k_right = false;

	cub->left_r = false;
	cub->right_r = false;

	cub->map = get_map();

	cub->fov = 0;
    cub->pos = 0;
    cub->direction = 0;

}

void exit_msg(t_cub *cub, char *str)
{
	ft_putstr_fd(2, str);
	exit(1);
}

void put_pixel(t_cub *cub, int x, int y, int color)
{
	mlx_pixel_put(cub->mlx_con, cub->mlx_win, x, y, color);
}

void put_square(t_cub *cub, int x, int y, int size, int color)
{
	
	for (int  i = 0; i < size; i++)
		put_pixel(cub, x + i , y, color);
	
	for (int  i = 0; i < size; i++)
		put_pixel(cub, x  , y + i, color);
	
	for (int  i = 0; i < size; i++)
		put_pixel(cub, x + i  , y + size, color);

	for (int  i = 0; i < size; i++)
		put_pixel(cub, x + size , y + i, color);
}


void start_cub(t_cub *cub)
{
    cub->mlx_con = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx_con,
			(BLOCK * 15) + 1 , (BLOCK * 10) + 1, "so long");
	if (!cub->mlx_win)
		exit_msg(cub, "Can't init win.\n");
	mlx_hook(cub->mlx_win, 17, 0, (void *)close_window, cub);
}

void draw_map(t_cub *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                put_square(game, x * BLOCK, y * BLOCK, BLOCK, 0xff0000);
}

/* void draw_map(t_cub *cub)
{
	char **mp  = cub->map;
	for (int x = 0; mp[x]; x++)
	{
		for (int y = 0; mp[y]; y++)
		{
			if (mp[x][y] == '1')
				put_square(cub, x*BLOCK , y*BLOCK, BLOCK);
		}
		
	}
	
} */




void move_player(t_cub *cub)
{

	float speed = 0.2;
/*  */
	float angle_speed = 0.015;
	float cos_angl = cos(cub->angle);
	float sin_angl = sin(cub->angle);

	if (cub->left_r)
		cub->angle -= angle_speed;
	if (cub->right_r)
		cub->angle += angle_speed;
	if (cub->angle <=  0)
		cub->angle += 2 * PI;
	if (cub->angle > 2 * PI)
		cub->angle =0;//  2 * PI;
/*  */

	if( (cub->k_up ) ) //&& (cub->py - speed > 0))
	{
		cub->px += cos_angl * speed;
		cub->py += sin_angl * speed;
	}
	if( (cub->k_down) )//&& ( cub->py + speed  < (300)))
		{
			cub->px -= cos_angl * speed;
			cub->py -= sin_angl * speed;
		}
	if( (cub->k_right) )//&& (  cub->px + speed < (300)))
		{
			cub->px -= sin_angl * speed;
			cub->py += cos_angl * speed;
		}
	if( (cub->k_left) )//&& (cub->px - speed > 0 ))
		{
			cub->px += sin_angl * speed;
			cub->py -= cos_angl * speed;
		}
}

void clear_win(t_cub *cub)
{
	for (int i = BLOCK + 1; i < (BLOCK * 14); i++)
	{
		for (int j = BLOCK + 1; j < (BLOCK * 9); j++)
		{
			put_pixel(cub, i,j, 0x000000);
		}
	}
}

int key_press(int kcode, t_cub *cub)
{
	if (kcode == W)
		cub->k_up = true;
	if (kcode == S)
		cub->k_down = true;
	if (kcode == A)
		cub->k_left = true;
	if (kcode == D)
		cub->k_right = true;
	if (kcode == LEFT)
		cub->left_r = true;
	if (kcode == RIGHT)
		cub->right_r = true;
	if (kcode == 113 ||kcode == 65307) 
		exit(1);
	return 0;
}

int key_release(int kcode, t_cub *cub)
{
    if(kcode == W)
        cub->k_up = false;
    if(kcode == S)
        cub->k_down = false;
    if(kcode == A)
        cub->k_left = false;
    if(kcode == D)
        cub->k_right = false;
    if(kcode == LEFT)
        cub->left_r = false;
    if(kcode == RIGHT)
        cub->right_r = false;
    return 0;
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000000000001";
    map[4] = "100000000000001";
    map[5] = "100000000000001";
    map[6] = "100000000000001";
    map[7] = "100000000011001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

bool colision(float px, float py, t_cub *cub)
{
	int x = (px / BLOCK);
	int y = (py / BLOCK);

	if (cub->map[y][x] == '1')
		return true;

	return false;
}

void draw_line(t_cub *cub, float angl_start, int i)
{
	
	float cos_ang = cos(angl_start);
	float sin_ang = sin(angl_start);
	float rx = cub->px;
	float ry = cub->py;
	while(!colision(rx, ry, cub))
	{
		put_pixel(cub, rx, ry , 0x00FFF0);
		rx += cos_ang; 
		ry += sin_ang; 
	}
}

int draw_loop(t_cub *cub)
{
	move_player(cub);
	clear_win(cub);
	put_square(cub, cub->px,cub->py, BLOCK, 0xfff000);
	draw_map(cub);
	
	float fract = (PI / 3) / (WIDTH) ;//* 2;//* 10;// / WIDTH;
	float start_x  =  cub->angle -  (PI / 6);
	int i = 0; 
	while(i < WIDTH)
	{
		draw_line(cub, start_x, i);
		start_x += fract; 
		i++;
	}	
	
		//draw_line(cub);
		//cub->angle += 0.1;
		//printf("%d", i);
	return 0;
}

int main(int ac, char *av[])
{
    t_cub	cub;
	if (0/* ac != 2 */) // CHANGE THIS
		return (ft_putstr_fd(2, "Error: Wrong nbr of args\n"), 1);
	init_cub(&cub);
	start_cub(&cub);

	//put_square(&cub,(WIDTH * PIXEL) / 2 , (HEIGH * PIXEL) / 2);
	mlx_hook(cub.mlx_win,2, 1L<<0, key_press, &cub);
	mlx_hook(cub.mlx_win,3, 1L<<1, key_release, &cub);

	mlx_loop_hook(cub.mlx_con, draw_loop, &cub);
	
	mlx_loop(cub.mlx_con);
    return 0;
}
