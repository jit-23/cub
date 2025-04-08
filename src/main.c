/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:05 by fde-jesu          #+#    #+#             */
/*   Updated: 2025/04/08 01:19:48 by fde-jesu         ###   ########.fr       */
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

void close_window(void)
{
	exit(0);
}
void start_cub(t_cub *cub)
{
    cub->mlx_con = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx_con,
			(WIDTH) , HEIGH, "cub");
	if (!cub->mlx_win)
		exit_msg(cub, "Can't init win.\n");
	
mlx_hook(cub->mlx_win, 17, 0, (void *)close_window, cub);
	cub->img = mlx_new_image(cub->mlx_con, WIDTH, HEIGH);
	cub->img_address = mlx_get_data_addr(cub->img , &cub->bpp,  &cub->size_line, &cub->endian);
	mlx_put_image_to_window(cub->mlx_con, cub->mlx_win, cub->img, 0, 0);
	//cub->imgs[0].x = 0;
	//cub->imgs[0].y = 0;
	
	if (!(cub->imgs[0].x))
		perror("non existent");
	if (!(cub->imgs[0].y))
		perror("non existent");
	if (access("textures/grass.xpm", F_OK) == -1)
		perror("File access error");
	else
		printf("done \n");
	//printf("%p\n", mlx_xpm_file_to_image(cub->mlx_con, "../textures/grass.xpm", &(cub->imgs[1].x), &(cub->imgs[1].y)));
	
	cub->imgs[0].img = mlx_xpm_file_to_image(cub->mlx_con, "textures/Fox.xpm", &(cub->imgs[0].x), &(cub->imgs[0].y));
	printf("%p\n", cub->imgs[0].img);
	printf("%d\n", cub->imgs[0].x);
	printf("%d\n", cub->imgs[0].y);
	/* OUTPUT :
	 0x102ae300
	 3632
	 0
	if (!cub->imgs[0].img)  // Check if image was loaded
	{
		printf("Error: Failed to load texture '../textures/grass.xpm'\n");
		exit(1);
	}
	printf("Texture loaded successfully\n");
	  
	cub->imgs[0].addr = mlx_get_data_addr(cub->imgs[0].img, &cub->imgs[0].bpp, &cub->imgs[0].size_line, &cub->imgs[0].endian);
	//cub->imgs[1].img = mlx_xpm_file_to_image(cub->mlx_con, "../egg/grass.xpm", &(cub->imgs[1].x), &(cub->imgs[1].y));
	if (!cub->imgs[0].addr)
	{
		printf("%p\n",cub->imgs[0].addr);
	}
	*/
}
	
void init_cub(t_cub *cub)
{

		//if (!cub->imgs)
		//{
		//	printf("Memory allocation failed\n");
		//	exit(1);
		//}
		
			cub->px = WIDTH / 2;//(WIDTH) /2;
	cub->py = HEIGH / 2;//(HEIGH) /2; 

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
/*
void put_pixel(int x, int y, int color, t_game *game)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
} */
	
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

/*  */
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
/*  */

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
/* 
void draw_line(t_cub *cub, float angl_start, int i)
{
	float cos_ang = cos(angl_start);
float sin_ang = sin(angl_start);
float rx = cub->px;
float ry = cub->py;
while(!colision(rx, ry, cub))
{
	 if (cos_ang >= 0 && sin_ang >= 0) //  1Q 
	{
		put_pixel(cub, rx, ry , 0x00FFF0);
		printf("123\n");
	}
	if (cos_ang <= 0 && sin_ang >= 0) // 2Q
	{
		put_pixel(cub, rx, ry , 0xFFFF0F);
		printf("2Q\n");
	}
	if (cos_ang <= 0 && sin_ang <= 0) // 3Q 
		put_pixel(cub, rx, ry , 0x00FFF);
	if (cos_ang >= 0 && sin_ang <= 0) // 4Q 
		//put_pixel(cub, rx, ry , 0x00FFFF); 
	//printf("cos_ang %f\n", cos_ang);
	//printf("sin_ang %f\n", sin_ang);
	rx += cos_ang * 0.05; 
	ry += sin_ang * 0.05; 
}
float dist = distance(cub, cub->px,cub->py, rx, ry);//sqrt(((rx - cub->px) * (rx - cub->px)) + ((ry - cub->py) * (ry - cub->py)));
//	float dist = sqrt(((rx - cub->px) * (rx - cub->px)) + ((ry - cub->py) * (ry - cub->py)));
float heigh = (((BLOCK) / dist) * ((WIDTH) / 2));
float start_y = (HEIGH - heigh) / 2;
//printf("start_y - %f\n", start_y);
float end = start_y + heigh;
///printf("end - %f\n", end);
while(start_y < end)
{
	if (cos_ang >= 0 && sin_ang >= 0) //  1Q 
		put_pixel(cub, i, start_y , 0xF0F0F);
	if (cos_ang <= 0 && sin_ang >= 0) // 2Q
		put_pixel(cub, i, start_y , 0xFF);
	if (cos_ang <= 0 && sin_ang <= 0) // 3Q 
		put_pixel(cub, i, start_y , 0xFF0F);
	if (cos_ang >= 0 && sin_ang <= 0) // 4Q 
		put_pixel(cub, i, start_y , 0xFF0FF);
	//put_pixel(cub, i, start_y, 0xFF000F);
	start_y++;
}
} */

static void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

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
 float perpWallDist;	

  //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
  if(side == 0) perpWallDist = (sideDistX - deltaDistX);
  else          perpWallDist = (sideDistY - deltaDistY);

  //Calculate height of line to draw on screen
  int lineHeight = (int)(HEIGH / perpWallDist);

  //calculate lowest and highest pixel to fill in current stripe
  int drawStart = -lineHeight / 2 + HEIGH / 2;
  if(drawStart < 0) drawStart = 0;
  int drawEnd = lineHeight / 2 + HEIGH / 2;
  if(drawEnd >= HEIGH) drawEnd = HEIGH - 1;
  //texturing calculations
  int texNum = cub->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

  //calculate value of wallX
  double wallX; //where exactly the wall was hit
  if (side == 0) wallX = mapY + perpWallDist * rayDirY;
  else           wallX = mapX + perpWallDist * rayDirX;
  wallX -= floor((wallX));

  //x coordinate on the texture
  int texWidth  = 32;
  int texHeight  = 32;
  int texX = (wallX * ((double)texWidth));
  if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
  if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

  // How much to increase the texture coordinate per screen pixel
  double step = 1.0 * texHeight / lineHeight;
  // Starting texture coordinate
  double texPos = (drawStart - HEIGH / 2 + lineHeight / 2) * step;
  for(int y = drawStart; y<drawEnd; y++)
  {
	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
	int texY = (int)texPos & (texHeight - 1);
	texPos += step;

	
	
	int color = *(int *)(cub->imgs[0].addr + texWidth * texY + texX);
	//int color = *(int *) cub->imgs[0].addr/* texture[texNum][texWidth * texY + texX] */;
	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	//if(side == 1) color = (color >> 1) & 8355711;
	//buffer[y][x] = color;
	
}

}
}







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

int draw_loop(t_cub *cub)
{
	//usleep(166667);
	clear_win(cub);
	move_player(cub);
	//put_square(cub, cub->px,cub->py, BLOCK, 0xfff000);
	//draw_map(cub);
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx_con, cub->mlx_win, cub->img, 0, 0);

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
