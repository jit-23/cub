/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:15:37 by fde-jesu          #+#    #+#             */
/*   Updated: 2025/04/06 23:06:54 by fde-jesu         ###   ########.fr       */
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
void calculate_distance(t_cub *cub);
void cast_rays(t_cub *cub);
void put_pixel(t_cub *cub, int x, int y, int color);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);


void my_mlx_pixel_put(t_img *img, int x, int y, int color) // img = cub->imgs[1]
{
	/* if (!img || !img->addr)
	{
		printf("111111111\n");
		return;
	}
	if (x < 0 || y < 0 || x >= img->x || y >= img->y)
	{
		printf("111222222222111111\n");
		return;
	} */
	char *dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
int draw_loop(t_cub *cub)
{
	//usleep(166667);
	clear_win(cub);
	move_player(cub);
	//put_square(cub, cub->px,cub->py, BLOCK, 0xfff000);
	//draw_map(cub);
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx_con, cub->mlx_win, cub->imgs[1].img, 0, 0);
	return 0;
}

/* void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst = NULL;
    if (img->addr == NULL)
		printf("noooo\n");
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	printf("asd\n");
} */

void close_window(void)
{
	exit(0);
}
void start_cub(t_cub *cub)
{
    cub->mlx_con = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx_con, (WIDTH) , HEIGH, "cub");
	if (!cub->mlx_win)
		exit_msg(cub, "Can't init win.\n");
	mlx_hook(cub->mlx_win, 17, 0, (void *)close_window, cub);
	cub->img = mlx_new_image(cub->mlx_con, WIDTH, HEIGH);
	cub->img_address = mlx_get_data_addr(cub->img , &cub->bpp,  &cub->size_line, &cub->endian);
	mlx_put_image_to_window(cub->mlx_con, cub->mlx_win, cub->img, 0, 0);
	if (!(cub->imgs[0].x))
		perror("non existent");
	if (!(cub->imgs[0].y))
		perror("non existent");
	if (access("textures/grass.xpm", F_OK) == -1)
		perror("File access error");
	else
		printf("done \n");
	cub->imgs[0].img = mlx_xpm_file_to_image(cub->mlx_con, "textures/3.xpm", &(cub->imgs[0].x), &(cub->imgs[0].y));
	printf("%p\n", cub->imgs[0].img);
	printf("%d\n", cub->imgs[0].x);
	printf("%d\n", cub->imgs[0].y);
	cub->imgs[0].addr = mlx_get_data_addr(cub->imgs[0].img, &cub->imgs[0].bpp, &cub->imgs[0].size_line, &cub->imgs[0].endian);
	/* img 1 is the main screen */cub->imgs[1].img = mlx_new_image(cub->mlx_con, WIDTH, HEIGH);
	/* img 1 is the main screen */cub->imgs[1].addr = mlx_get_data_addr(cub->imgs[1].img, &cub->imgs[1].bpp, &cub->imgs[1].size_line, &cub->imgs[1].endian);
	
//	printf("addr %p\n", cub->imgs[0].addr);
//	printf("bpp %d\n", cub->imgs[0].bpp);
//	printf("sizeline %d\n", cub->imgs[0].size_line);
//	printf("endian %d\n", cub->imgs[0].endian);
	//mlx_put_image_to_window(cub->mlx_con, cub->mlx_win, cub->imgs[0].img, 40,40 );
}
	
void init_cub(t_cub *cub)
{

	cub->px = WIDTH / 12;//(WIDTH) /2;
	cub->py = HEIGH / 12;//(HEIGH) /2;

	cub->angle  = PI/2;
	cub->speed = 0.5;
	cub->angle = NORTH;

	cub->sin = 1;
	cub->cos = 0;
	
	cub->k_up = false;
    cub->k_down = false;
    cub->k_left = false;
    cub->k_right = false;
	cub->k_plus = false;
	cub->k_less = false;
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




void draw_map(t_cub *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                put_square(game, x * BLOCK, y * BLOCK, BLOCK, 0xff0000);
}

void move_player(t_cub *cub)
{
	float angle_speed = 0.01;
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
	if( (cub->k_up ) ) //&& (cub->py - speed > 0))
	{
		cub->px += cos_angl * cub->speed;
		cub->py += sin_angl * cub->speed;
	}
	if( (cub->k_down) )//&& ( cub->py + cub->speed  < (300)))
		{
			cub->px -= cos_angl * cub->speed;
			cub->py -= sin_angl * cub->speed;
		}
	if( (cub->k_right) )//&& (  cub->px + cub->speed < (300)))
		{
			cub->px -= sin_angl * cub->speed;
			cub->py += cos_angl * cub->speed;
		}
	if( (cub->k_left) )//&& (cub->px - speed > 0 ))
		{
			cub->px += sin_angl * cub->speed;
			cub->py -= cos_angl * cub->speed;
		}
}



int key_press(int kcode, t_cub *cub)
{
	printf("%d\n", kcode);
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
	if(kcode == LESS)
	    cub->speed-=2;//cub->right_r = true;
	if(kcode == PLUSS)
        cub->speed+=2;//cub->right_r = true;
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
	/* if(kcode == LESS)
        cub->right_r = false;
	if(kcode == PLUSS)
        cub->right_r = false; */
    return 0;
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 22);
    map[0] = "111111111111111111111111111111";
    map[1] = "100000000000000000000000000011";
    map[2] = "100000000000000000000000000011";
    map[3] = "100000000000000000000000000011";
    map[4] = "100000000000000000000000000011";
    map[5] = "100000000000000000000000000011";
    map[6] = "100000000000000000000000000011";
    map[7] = "100000000000000000000000000011";
    map[8] = "100000000000000000000000000011";
    map[9] = "100000000000000000000000000011";
    map[10] = "100000000000000000000000000011";
    map[11] = "100000000000000000000000000011";
    map[12] = "100000000000000000000000000011";
    map[13] = "100000000000000000000000000011";
    map[14] = "100000000000000000000000000011";
    map[15] = "100000000000000000000000000011";
    map[16] = "100000000000000000000000000011";
    map[17] = "111111111111111111111111111111";
    map[18] = NULL;
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

static float calc_dist(float x,float y)
{
	return (sqrt(x * x + y * y));
}

float distance(t_cub * cub,float x1 , float y1, float x2, float y2)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - cub->angle;
	float dist = (calc_dist(delta_x, delta_y) * cos(angle));
	return (dist);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////


void draw_line(t_cub *cub, float angl_start, int i)
{
 // **Player Position**
 int mapX = (int)cub->px;  
 int mapY = (int)cub->py;  


// **Ray Direction**
float rayDirX = cos(angl_start);
float rayDirY = sin(angl_start);

// **Step sizes**
float deltaDistX = fabs(1 / rayDirX);
float deltaDistY = fabs(1 / rayDirY);	// conseguir o valor absoluto do percurso que o RAIO  do  x/y tem que
										// percorrer para avancar 1 tile no grafico cartesiano.

/// **Calculate Initial Side Distances**
float sideDistX, sideDistY; // valores que x e y tem que percorrer para o RAIO dar o valor certo e bater 
// no vertice do tile seguinte 
int stepX, stepY; // valor positivo ou negativo para diferenciar o lado certo a percorrer

if (rayDirX < 0) { //esquerda
	stepX = -1; // valor para 
	sideDistX = (cub->px - mapX) * deltaDistX;
 } else {
	 stepX = 1;
	 sideDistX = (mapX + 1.0 - cub->px) * deltaDistX;
}

if (rayDirY < 0)
	{
		stepY = -1; // baixo
		sideDistY = (cub->py - mapY) * deltaDistY;
	} 
else {
	stepY = 1; // cima
	sideDistY = (mapY + 1.0 - cub->py) * deltaDistY;
 }
 
 // **DDA Raycasting Loop**

 int hit = 0;
 int side; // 0 = X wall, 1 = Y wall
 while (hit == 0) {
	 // Move in the direction of the shortest step
	if (sideDistX < sideDistY) {
		 sideDistX += deltaDistX;
		 mapX += stepX;
		 side = 0;
	} else {
		 sideDistY += deltaDistY;
		 mapY += stepY;
		 side = 1;
	}
	 // Check for a collision (wall hit)
	 if (colision(mapX, mapY, cub)) {
		 hit = 1;
	 }
 }

// **Calculate Distance to Wall**
 float perpWallDist;	
 if (side == 0)
	 perpWallDist = (mapX - cub->px + (1 - stepX) / 2) / rayDirX;
 else
	 perpWallDist = (mapY - cub->py + (1 - stepY) / 2) / rayDirY;

 // **Wall Height Calculation**
 perpWallDist *= cos(angl_start - cub->angle); // Correct for fish-eye effect
 float lineHeight = (BLOCK / perpWallDist) * (HEIGH / 2);
/* int lineHeight = (int)(HEIGH / perpWallDist)*/
 // **Determine Start and End Points for the Vertical Line**
 float drawStart = (HEIGH - lineHeight) / 2;
 float drawEnd = drawStart + lineHeight;

// **Draw the Wall Column**
double xwall;// = mapY + perpWallDist * rayDirY;

if (side == 0)
    xwall = cub->py + perpWallDist * rayDirY;
else
    xwall = cub->px + perpWallDist * rayDirX;
xwall -= floor(xwall);

xwall -= floor(xwall);

int texX=  (int) (xwall * (double)cub->imgs[0].x);
if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
    texX = cub->imgs[0].x - texX - 1;
int y = drawStart;
while(y < drawEnd)
{
	int color;
	int d = y*256 - HEIGH * 128 + lineHeight * 128;
	int texY = ((d * cub->imgs[0].y) / HEIGH) / 256;
	if (texY >= 0 && texY < cub->imgs[0].y && texX >= 0 && texX < cub->imgs[0].x)
	{
		color = *(int *)(cub->imgs[0].addr + (texY * cub->imgs[0].size_line + texX * (cub->imgs[0].bpp / 8) ));
		printf("%d\n", y);
		printf("%d\n", i);
	}
	else
		color = 0x000000;
	//printf("->>%d\n", color);
		//mlx_pixel_put(cub->mlx_con, cub->mlx_win, WIDTH/2 , HEIGH/2, color );
	
	my_mlx_pixel_put(&cub->imgs[1], i, y, color);
	y++;
}
}

//

void put_pixel(t_cub *cub, int x, int y, int color)
{
	if(x >= WIDTH || y >= HEIGH || x < 0 || y < 0)
        return;
	int index = y * cub->size_line + x * cub->bpp / 8;
//	mlx_pixel_put(cub->mlx_con, cub->mlx_win, x, y, color);
	cub->img_address[index] = color & 0xFF;
    cub->img_address[index + 1] = (color >> 8) & 0xFF;
    cub->img_address[index + 2] = (color >> 16) & 0xFF;

}

/* void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst = NULL;
    if (img->addr == NULL)
		printf("noooo\n");
	//printf("sum - %d\n", (y * img->size_line + x * (img->bpp / 8)));
	
	printf("bpp - %d\n", img->bpp / 8);
	printf("img->size_line - %d\n", img->size_line);
	printf("(y * img->size_line + x * (img->bpp / 8) =  ||%d||\n", (y * img->size_line + x * (img->bpp / 8)));
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	printf("x - %d\n", x);
	printf("y - %d\n", y);
	*(unsigned int*)dst = color;
} */



/* while(y < drawEnd)
{
	//("cub->imgs[0].size_line - %d\n", cub->imgs[0].size_line);
	//("HEIGH - %d\n", HEIGH);
	int d = y*256 - HEIGH * 128 + lineHeight * 128;
	int texY = ((d * cub->imgs[0].y) / HEIGH) / 256;
	//("......\n%p\n",cub->imgs[0].addr);
	////("d - %d\n", d);
	//("%d\n", texY);
	//("%d\n",cub->imgs[0].size_line);
	//("%d\n",texX);//cub->imgs[0].bpp / 8
	//("_%d\n",cub->imgs[0].bpp );//cub->imgs[0].bpp / 8
	int color = *(int *)(cub->imgs[0].addr + (texY * cub->imgs[0].size_line + texX * (cub->imgs[0].bpp / 8) ));
	//("----------------------------\n");
	//("->%d\n",  i);
	//("->%d\n",  y);
	my_mlx_pixel_put(&cub->imgs[0], i, y, color);
	//put_pixel(cub, i, y, color);
	//("----------------------------\n");

	y++;

} */


void cast_rays(t_cub *cub)
{

	float fraction = PI / 3 / WIDTH;
    float start_x = cub->angle - PI / 6;
    int i = 0;
    while(i < WIDTH)
    {
        draw_line(cub,  start_x, i);
        start_x += fraction;
        i++;
    }
	/* float fract = (PI / 3) / (WIDTH) ;
	printf("cub->angle = %f\n", cub->angle);
	float start_x  =  cub->angle -  (PI / 6);
	float i = 0; 
	while(i < WIDTH)
	{
		draw_line(cub, start_x, i);
		start_x += fract;
		i++;
	} */
}




void clear_win(t_cub *cub)
{
	
	//mlx_clear_window(cub->mlx_con,cub->mlx_win);
	for (int i = 0; i < (WIDTH); i++)
	{
		for (int j = 0; j < (HEIGH); j++)
		{
			put_pixel(cub, i,j, 0);
		}
	}

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
