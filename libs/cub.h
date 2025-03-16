#ifndef CUB_H
#define CUB_H

#include "libft/libft.h"
#include "mlx/mlx.h"

#include <stdbool.h> 
# include <curses.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# include <math.h>

#define W 119
#define S 115
#define D 100
#define A 97
#define LEFT 65361
#define RIGHT 65363

#define BLOCK 25

#define PI 3.14159

#define WIDTH 15 * 25
#define HEIGH 9 * 25
#define PIXEL 32

typedef struct s_cub
{
    void *mlx_con;
    void *mlx_win;
    int map_x;
    int map_y;

    /* player info */
    int fov;
    int pos;
    char **map;


    float px;
    float py;
    
    float angle;

    bool left_r;
    bool right_r;
    bool k_up;
    bool k_down;
    bool k_left;
    bool k_right;

    int direction;

}t_cub;
 

#endif