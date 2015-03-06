/*
** test.h for test in /home/gaspar_q/Entrainement igraph
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Wed Nov 26 10:00:37 2014 quentin gasparotto
** Last update Sun Dec 21 10:39:39 2014 quentin gasparotto
*/

#ifndef SYS_LIBX_H_
# define SYS_LIBX_H_

# include <stdlib.h>
# include <mlx.h>
# include "/usr/include/X11/X.h"
# include "wolf.h"

# define CLEAN		0
# define ERROR          -1
# define CLEARLY	3

# define SOK		3
# define HOME		2
# define ON		1
# define OFF		0

# define MALLOC_FAIL	NULL
# define MALLOC_ERR	-1

# define MLX_FAIL	-2
# define WDW_FAIL	-3
# define FLD_ERR	-4
# define BAD_FLD	-5
# define BAD_FD		-6
# define WRG_HGT	-7
# define EPTY		-8
# define TEXT_ERR	-9
# define ENV_ERR	-10

# define ESCAPE		65307
# define UP		65362
# define DOWN		65364
# define RIGHT		65363
# define LEFT		65361
# define RETURN		65293

typedef struct	s_field
{
  char		**char_field;
  int		width;
  int		height;
}		t_field;

typedef struct	s_image
{
  void		*img;
  unsigned char	*dat;
  int		bpp;
  int		wdth;
  int		hght;
  int		edn;
}		t_image;

typedef struct	s_point2d
{
  double	x;
  double	y;
  unsigned char	color[4];
}		t_point2d;

typedef struct	s_streight
{
  t_point2d	result;
  t_point2d	vec;
  t_point2d	origin;
}		t_streight;

typedef struct	s_system
{
  void		*mlx;
  void		*wdw;
  t_point2d	pos;
  double	alpha;
  t_image	sky_grd;
  t_image	walls;
  t_image	fnl_img;
  t_field	*field;
  int		game;
  char		bk;
  char		*file;
}		t_system;

int	expose_gestion(t_system *sys);
int	keyboard_gestion(int keycode, t_system *sys);
int	mouse_gestion(int button, int x, int y, t_system *sys);

int	get_color(t_system *sys, int color, int endian, unsigned char *tab_col);
int	put_pix_to_img(t_system *sys, t_image *img, t_point2d id, int color_hex);
int     get_final_img(t_system *sys);
int     init_sys_img(t_system *sys);
int     init_walls(t_system *sys);
int     mini_map_display(t_system *sys);
int	display_cursor(t_system *sys);

int	home(t_system *sys);
int	home_gestion(int keycode, t_system *sys);

int	load_texture(const int fd, t_system *sys, t_image *img);
int	init_color_tab(const int fd, unsigned int *color_tab, int color_nb);

int     get_view(t_system *sys, t_field *field, double alpha);
int     get_side(t_system *sys, int k, t_streight streight);
t_point2d search_walls(t_system *sys, t_point2d vec, int x, int *k);
int     disp_block(t_system *sys, t_streight streight, int x, int k);

t_field	*get_field(char *pathname);
int     free_my_field(t_field *field);
int     get_pos(t_system *sys, char out_pos);

#endif /* !SYS_LIBX_H_  */
