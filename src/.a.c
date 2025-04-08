
#include "../libs/cub.h"
#include "../libs/mlx/mlx.h"
// void init_cub(t_cub *cub)
// {
// 	//&textures[0].bpp, &textures[0].line_length, &textures[0].endian);
// 	/* cub->imgs = (t_img *)malloc(sizeof(t_img ) * 2);
// 	cub->imgs[0].img = mlx_xpm_file_to_image(cub->mlx_con,
// 		"../textures/grass.xpm", &(cub->imgs[0].x), &(cub->imgs[0].y));
// 	printf("asdada\n");
// 		cub->imgs[0].addr = mlx_get_data_addr(cub->imgs[0].img , &cub->imgs[0].bpp,  &cub->imgs[0].size_line, &cub->imgs[0].endian); */
// 		printf("1\n");
// 		//cub->imgs = (t_img *)malloc(sizeof(t_img) * 2);
// 		//cub->imgs = ft_calloc(2, sizeof(t_img));
// 		if (!cub->imgs)
// 		{
// 			printf("Memory allocation failed\n");
// 			exit(1);
// 		}
// 		printf("2\n");
// 		/* cub->imgs[0].img = */ /* mlx_xpm_file_to_image(cub->mlx_con, "../textures/egg.xpm", &(cub->imgs[0].x), &(cub->imgs[0].y)) */
// 		printf("%p\n", mlx_xpm_file_to_image(cub->mlx_con, "../textures/egg.xpm", &(cub->imgs[0].x), &(cub->imgs[0].y)));
// 		printf("%p\n", mlx_xpm_file_to_image(cub->mlx_con, "textures/egg.xpm", &(cub->imgs[0].x), &(cub->imgs[0].y)));
// 		printf("3\n");
		
// 		if (!cub->imgs[0].img)  // Check if image was loaded
// 		{
// 			printf("Error: Failed to load texture '../textures/grass.xpm'\n");
// 			exit(1);
// 		}
		
// 		printf("Texture loaded successfully\n");
		
// 		cub->imgs[0].addr = mlx_get_data_addr(cub->imgs[0].img, &cub->imgs[0].bpp, &cub->imgs[0].size_line, &cub->imgs[0].endian);
// 	printf("asdada\n");
// 	cub->imgs[1].img = mlx_xpm_file_to_image(cub->mlx_con,
// 			"../egg/grass.xpm", &(cub->imgs[1].x), &(cub->imgs[1].y));
// 	//cub->imgs[1].addr = mlx_get_data_addr(cub->imgs[1].img , &cub->imgs[1].bpp,  &cub->imgs[1].size_line, &cub->imgs[1].endian);

// 	cub->px = WIDTH / 12;//(WIDTH) /2;
// 	cub->py = HEIGH / 12;//(HEIGH) /2; 

// 	cub->angle  = PI/2;
	
// 	cub->speed = 0.5;
// 	cub->angle = NORTH;
	
// 	cub->sin = 1;
// 	cub->cos = 0;
	
// 	cub->k_up = false;
//     cub->k_down = false;
//     cub->k_left = false;
//     cub->k_right = false;
// 	cub->k_plus = false;
// 	cub->k_less = false;
// 	cub->left_r = false;
// 	cub->right_r = false;

// 	cub->map = get_map();
// 	cub->fov = 0;
//     cub->pos = 0;
//     cub->direction = 0;

// }

// int main(int ac, char *av[])
// {
//     t_cub	cub;
// 	if (0/* ac != 2 */) // CHANGE THIS
// 		return (ft_putstr_fd(2, "Error: Wrong nbr of args\n"), 1);
// 	init_cub(&cub);
// 	start_cub(&cub);
// 	//put_square(&cub,(WIDTH * PIXEL) / 2 , (HEIGH * PIXEL) / 2);
// 	mlx_hook(cub.mlx_win,2, 1L<<0, key_press, &cub);
// 	mlx_hook(cub.mlx_win,3, 1L<<1, key_release, &cub);

// 	mlx_loop_hook(cub.mlx_con, draw_loop, &cub);
	
// 	mlx_loop(cub.mlx_con);
//     return 0;
// }


int main()
{
    void *mlx;
    void *win;
    void *img;
    int img_width, img_height;

    // Initialize MLX
    mlx = mlx_init();
    if (!mlx)
        return (1);

    // Create a window
    win = mlx_new_window(mlx, 800, 600, "XPM Image Example");

    // Load the XPM image
	printf("%d\n", img_height);
	printf("%d\n", img_width);
    img = mlx_xpm_file_to_image(mlx, "textures/Fox.xpm", &img_width, &img_height);
    if (!img)
    {
        printf("Failed to load image\n");
        return (1);
    }
	printf("%d\n",img);
    // Put the image in the window
    mlx_put_image_to_window(mlx, win, img, 100, 100);

    // Loop to keep the window open
    mlx_loop(mlx);
    
    return (0);
}

//////////////////////////////

  //start the main loop
  while(!done())
  {
    for(int x = 0; x < w; x++)
    {
      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);
      //calculate ray position and direction
      double cameraX = 2*x/double(w)-1; //x-coordinate in camera space
      double rayDirX = dirX + planeX*cameraX;
      double rayDirY = dirY + planeY*cameraX;


      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }




      /////////////////////////////////////////////
      ///////////////////////////////////////

    float step = 1.0 * cub->imgs[0].y / lineHeight;
    float texPos = (drawStart - HEIGH / 2 + lineHeight / 2) * step;

for (int y = drawStart; y < drawEnd; y++) {
	int texY = (int)texPos;
	texPos += step;

	if (texX >= 0 && texX < cub->imgs[0].x &&
		texY >= 0 && texY < cub->imgs[0].y)
	{
		color = *(int *)(cub->imgs[0].addr +
			   (texY * cub->imgs[0].size_line +
			    texX * (cub->imgs[0].bpp / 8)));
	}
	else color = 0x000000;

	my_mlx_pixel_put(&cub->imgs[1], i, y, color);
}//double texPos = (double)(drawStart - HEIGH / 2 + lineHeight / 2) * step;