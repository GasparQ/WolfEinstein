/*
** get_view.c for get my screen in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Wed Dec  3 16:32:18 2014 quentin gasparotto
** Last update Sat Dec 20 14:27:42 2014 quentin gasparotto
*/

#include <math.h>
#include "./include/minilibx_objects.h"
#include "./include/wolf.h"
#include "./include/my.h"

int		init_walls(t_system *sys)
{
  int		rank;
  unsigned char	color[4];

  get_color(sys, 0xFF000000, sys->walls.edn, &color[0]);
  rank = 0;
  while (rank < 640 * 640 * 4)
    {
      sys->walls.dat[rank] = color[rank % 4];
      rank++;
    }
  return (CLEAN);
}

int		walls_border(t_system *sys, int x, int *len)
{
  t_point2d	bord;

  bord.x = x;
  bord.y = 320 - (*len);
  put_pix_to_img(sys, &(sys->walls), bord, WHITE);
  bord.y = 320 + (*len);
  put_pix_to_img(sys, &(sys->walls), bord, WHITE);
  *len = (*len) - 1;
  return (CLEAN);
}

int		display_walls(t_system *sys, int x, int len, int side)
{
  t_point2d	height;
  unsigned char col[4];
  int           rank;

  walls_border(sys, x, &len);
  get_color(sys, side, sys->walls.edn, &col[0]);
  while (len >= 0)
    {
      height.x = 4 * x + (320 - len) * sys->sky_grd.wdth;
      height.y = 4 * x + (320 + len) * sys->sky_grd.wdth;
      rank = 0;
      while (rank < 4)
        {
          sys->walls.dat[(int)height.x + rank] = col[rank];
          sys->walls.dat[(int)height.y + rank] = col[rank];
          rank++;
        }
      len = len - 1;
    }
  return (1);
}

t_point2d	search_walls(t_system *sys, t_point2d vec, int x, int *k)
{
  t_streight	streight;

  streight.result.x = (sys->pos.x + (vec.x / 100) * (*k)) / 100;
  streight.result.y = (sys->pos.y + (vec.y / 100) * (*k)) / 100;
  streight.vec = vec;
  while (streight.result.x >= 0 &&
	 streight.result.x < sys->field->width &&
	 streight.result.y >= 0 &&
	 streight.result.y < sys->field->height)
    {
      if (disp_block(sys, streight, x, *k) == 1)
	return (streight.result);
      (*k) = (*k) + 1;
      streight.result.x = (sys->pos.x + (vec.x / 100) * (*k)) / 100;
      streight.result.y = (sys->pos.y + (vec.y / 100) * (*k)) / 100;
    }
  return (streight.result);
}

int		get_view(t_system *sys, t_field *field, double alpha)
{
  t_point2d	pos_scr;
  t_point2d	scrn_pos;
  t_point2d	vector;
  int		x;
  int		inter;
  int		k;

  x = 0;
  init_walls(sys);
  while (x < sys->walls.wdth / 4)
    {
      pos_scr.x = 50.0;
      inter = 320.0 - x;
      pos_scr.y = (inter / 640.0) * 100.0;
      scrn_pos.x = pos_scr.x * cos(alpha) - pos_scr.y * sin(alpha) + sys->pos.x;
      scrn_pos.y = pos_scr.x * sin(alpha) + pos_scr.y * cos(alpha) + sys->pos.y;
      vector.x = scrn_pos.x - sys->pos.x;
      vector.y = scrn_pos.y - sys->pos.y;
      k = 100;
      search_walls(sys, vector, x, &k);
      x = x + 1;
    }
  get_final_img(sys);
  mlx_put_image_to_window(sys->mlx, sys->wdw, sys->fnl_img.img, 0, 0);
  return (CLEAN);
}
