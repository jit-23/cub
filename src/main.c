/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:05 by fde-jesu          #+#    #+#             */
/*   Updated: 2025/03/15 06:36:40 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub.h"
#include "../libs/mlx/mlx.h"


void start_cub(t_cub *cub);
void init_cub(t_cub *cub);
void exit_msg(t_cub *cub, char *str);
void put_square(t_cub *cub , int x , int y);
int key_press(int kcode, t_cub *cub);
void close_window(void);
void move_player(t_cub *cub);
int  draw_loop(t_cub *cub);
void clear_win(t_cub *cub);


void close_window(void)
{
	exit(0);
}

void init_cub(t_cub *cub)
{

	cub->px = (WIDTH*PIXEL) /2 ;
	cub->py = (HEIGH*PIXEL)/2;

	cub->k_up = false;
    cub->k_down = false;
    cub->k_left = false;
    cub->k_right = false;
	cub->left_r = false;
	cub->right_r = false;

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

void put_square(t_cub *cub, int x, int y)
{
	
	int size = 10;
	for (int  i = 0; i < size; i++)
		put_pixel(cub, x + i , y, 0xff0000);
	
	for (int  i = 0; i < size; i++)
		put_pixel(cub, x  , y + i, 0xff0000);
	
	for (int  i = 0; i < size; i++)
		put_pixel(cub, x + i  , y + size, 0xff0000);

	for (int  i = 0; i < size; i++)
		put_pixel(cub, x + size , y + i, 0xff0000);
}

void start_cub(t_cub *cub)
{
    cub->mlx_con = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx_con,
			WIDTH * PIXEL, HEIGH * PIXEL, "so long");
	if (!cub->mlx_win)
		exit_msg(cub, "Can't init win.\n");
	mlx_hook(cub->mlx_win, 17, 0, (void *)close_window, cub);
}

int draw_loop(t_cub *cub)
{
	move_player(cub);
	clear_win(cub);
	put_square(cub, cub->px,cub->py);
	return 0;
}

void move_player(t_cub *cub)
{

	float speed = 10;
/*  */
	float angle_speed = 0.6;
	float cos_angl = cos(cub->angle);
	float sin_angl = sin(cub->angle);

	if (cub->left_r)
		cub->angle -= angle_speed;
	if (cub->right_r)
		cub->angle += angle_speed;
	if (cub->angle <  0)
		cub->angle += 2 * PI;
	if (cub->angle > 2 * PI)
		cub->angle -=  2 * PI;
/*  */

	if (cub->k_up && (cub->py - speed > 0))
	{
		cub->px += cos_angl * speed;
		cub->py += sin_angl * speed;
	}
	if (cub->k_down && ( cub->py + speed  < (HEIGH*PIXEL)))
		{
			cub->px -= cos_angl * speed;
			cub->py -= sin_angl * speed;
		}
	if (cub->k_right && (  cub->px + speed < (WIDTH*PIXEL)))
		{
			cub->px -= cos_angl * speed;
			cub->py += sin_angl * speed;
		}
	if (cub->k_left && (cub->px - speed > 0 ))
		{
			cub->px += cos_angl * speed;
			cub->py -= sin_angl * speed;
		}
		/* cub->px -= speed; */


	// if (cub->k_up && (cub->py - speed > 0  /* && cub->py < (HEIGH*PIXEL) */))
	// 	cub->py -= speed;
	// if (cub->k_down && (/* cub->py > 1  && */ cub->py + speed  < (HEIGH*PIXEL)))
	// 	cub->py += speed;
	// if (cub->k_right && (/* cub->px > 0 &&*/  cub->px + speed < (WIDTH*PIXEL)))
	// 	cub->px += speed;
	// if (cub->k_left && (cub->px - speed > 0  /* && cub->px < (WIDTH*PIXEL) */))
	// 	cub->px -= speed;
}

void clear_win(t_cub *cub)
{
	for (int i = 0; i < (WIDTH * PIXEL); i++)
	{
		for (int j = 0; j < (HEIGH * PIXEL); j++)
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




int main(int ac, char *av[])
{
    t_cub cub;
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

