#ifndef MAIN_H
#define MAIN_H

#  define BUFFER_SIZE 42
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include "libft/libft.h"

//// minimap

# define MINIW 180
# define MINIH 120

# define MINIW2 360
# define MINIH2 240

////////////


///// 
# define WIDTH 1280
# define HEIGHT 720
# define SCALE 20
//

//////// keys for key hook
# define ANGLE 0.1
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define ESC 65307
//////////////////

////// colors
# define GRAY 0x767676
# define DARKFACTOR 30
//////////////

//////PLAYER CARACTERS
#define PLAYERVET 1

/// door
# define DISTDOOR 20
# define DOOR 1337

# define MAXWALL 500
typedef struct s_cordonate
{
    double  x;
    double  y;
    double   dist;
    int     view;
    int      is_door;
    int        x_door;
    int        y_door;
}               t_cordonate;

typedef struct s_vector
{
    double  x;
    double  y;
}              t_vector;
/////////////

typedef struct s_map_file
{
    int fd;
    char *av;
}t_map_file;

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}           t_texture;

typedef struct s_map_info
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *F;
    char *C;
    char **map;
    int map_index;
    int texture_number;
    char *line;
    int height;
    int width;
    int arr_len;
    char *mapstr;
    double direction;
    int     maptype;
}           t_map_info;

typedef struct s_vars
{
    int x;
    int y;
    int length;
    char *ft_split;
    int count;
}               t_vars;


typedef struct s_color
{
    int     r;
    int     g;
    int     b;
    int     color;
}               t_color;

typedef struct s_img
{
    void        *win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}               t_img;

typedef struct s_mouves
{
    double  left;
    double  right;
    double  up;
    double  down;
}              t_mouves;


typedef struct s_mlx
{
    /////
    void        *win3d;
	void		*img3d;
	char		*addr3d;
	int			bits_per_pixel3d;
	int			line_length3d;
	int			endian3d;
    double jump;
    void        *mlx;
    void        *win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
    double  face;
    t_mouves    mouves;
    t_map_file  map_file;
    t_map_info  map_info;
    t_vars      vars;
    t_cordonate	Player;
    t_cordonate ToMouve;
    t_color ceil;
    t_color floor;
    t_texture   NO;
    t_texture   SO;
    t_texture   WE;
    t_texture   EA;
    t_texture door;
    t_texture torch[14];
}               t_mlx;

// parsing functions
char	*get_next_line(int fd);
void parsing(t_mlx *mlx_data);
void reading_textures(t_mlx *mlx_data);
void parsing_map(t_mlx *mlx_data);
void map_rules(t_mlx *mlx_data);
int line_rules(t_mlx *mlx_data);
void free_split(char **split);
void free_infos(t_mlx *mlx_data);
int line_rules(t_mlx *mlx_data);
void map_rules(t_mlx *mlx_data);
int ft_arrlen(char **map);
int ft_check_extension(char *str, char *ext);
void ft_free_one(t_mlx *mlx_data, char *line, char *parse_msg);
void ft_free_two(t_mlx *mlx_data, char **split);
int	check_count(char **split);
int	invalid_char(char **split);
int how_many_commas(char *texture);
int	check_rgb(char *texture);
int	contain_one_only(char *texture);
void	parse_line(t_mlx *mlx_data, char *line);
int	map_height_width(t_mlx *mlx_data);
void	check_player_count(t_mlx *mlx_data, int count);
void ft_free_two(t_mlx *mlx_data, char **split);
void check_errors(t_mlx *mlx_data);
void	check_player_conditions(int x, int y, t_mlx *mlx_data);
int color_value(t_mlx *data, int flag);
void texture_init(t_mlx *mlx_data);
void freeing(t_mlx *mlx_data);
void doors_check(t_mlx *mlx_data);
int torch_animation(t_mlx *mlx_data);
int floor_color_value(t_mlx *data);
int ceil_color_value(t_mlx *data);
int torch_animation(t_mlx *mlx_data);
void torch_texture_innit(t_mlx *mlx_data);
void	get_img_addr(t_mlx *mlx_data);
void check_player_direction(t_mlx *mlx_data);
int gate_animation(t_mlx *data);
// raycasting


//raycasting functions

void	initialize(t_mlx	*mlx);
t_cordonate GetPlayerPosition(char **map);
void    StandardMap(t_mlx *mlx_data);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int IsPlayer(char c);
int get_texel(t_mlx *data ,t_texture texture, int x, int y);


t_cordonate min_of(t_cordonate H, t_cordonate V);
t_cordonate max_of(t_cordonate H, t_cordonate V);
int max(int a, int b);
void    ranging(int *x0, int *y0, int *x1, int *y1);
int isNeer(t_cordonate *A, t_cordonate Player);
int	is_wall(t_mlx *data, t_cordonate *A);
void    fillmouves(t_mlx *data);
int shadding(unsigned int color, double dist, int factor);
void    drow_floor(t_mlx *mlx, int color);
void    drow_ciell(t_mlx *mlx, int x, int y, int color);
t_cordonate init_H_intersection(t_cordonate P, double angle, t_cordonate *deff);
t_cordonate	HorizontalIntersection(t_mlx *data, double angle_dif);
void init_V_intersection(t_cordonate P, double angle, t_cordonate *A, t_cordonate *deff);
t_cordonate	VerticalIntersection(t_mlx *data, double angle_dif);
void    AddDirection(t_mlx *data, int W, int H);
int is_in_range(t_cordonate Player, int maptype, int i, int j);
void    fill_WH(t_cordonate *WH, int maptype);
void    putColorToMini(t_mlx *data, int i, int j);
void    DrowMiniMap(t_mlx *data);
void   RayCasting(t_mlx *data);
void    StandardMap(t_mlx *data);
int get_texel(t_mlx *data ,t_texture texture, int x, int y);
t_texture *init_texture(t_mlx *data, t_cordonate Intersection);
int    puttexel(t_mlx *data ,t_texture *texture, t_cordonate tex_cord[], int is_door);
void init_texture_coords(t_cordonate Intersection, t_texture *textures, t_cordonate tex_cord[2]);
void putingTexture(t_mlx *data, double wall, t_cordonate Intersection, int x);


#endif 