/*
** put_pixel.c for function to put a pixel into an image in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Dec 18 16:03:37 2014 quentin gasparotto
** Last update Thu Dec 18 16:58:33 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"

int	get_color(t_system *sys, int color, int endian, unsigned char *tab_col)
{
  color = mlx_get_color_value(sys->mlx, color);
  if (endian == 0)
    {
      tab_col[0] = color % 256;
      tab_col[1] = (color >> 8) % 256;
      tab_col[2] = (color >> 16) % 256;
      tab_col[3] = (color >> 24) % 256;
    }
  else
    {
      tab_col[3] = color % 256;
      tab_col[2] = (color >> 8) % 256;
      tab_col[1] = (color >> 16) % 256;
      tab_col[0] = (color >> 24) % 256;
    }
  return (CLEAN);
}

int		put_pix_to_img(t_system *sys, t_image *img, t_point2d id, int color_hex)
{
  int           coord;
  int           rank;
  unsigned char color[4];

  get_color(sys, color_hex, img->edn, &color[0]);
  coord = (int)id.x * 4 + (int)id.y * img->wdth;
  rank = 0;
  while (rank < 4)
    {
      img->dat[coord + rank] = color[rank];
      rank = rank + 1;
    }
  return (CLEAN);
}
