/*
** get_graph.c for get graphics properties in /home/gaspar_q
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Dec  2 16:06:45 2014 quentin gasparotto
** Last update Sun Dec 21 10:43:21 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/my.h"
#include <mlx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

int		display_cursor(t_system *sys)
{
  int		alpha;
  t_point2d	circle;
  int		radius;

  alpha = 0;
  radius = 5;
  while (alpha <= 360)
    {
      circle.x = WIDTH / 2 + radius * cos((double)alpha * M_PI / 180.0);
      circle.y = HEIGHT / 2 + radius * sin((double)alpha * M_PI / 180.0);
      put_pix_to_img(sys, &(sys->fnl_img), circle, BLACK);
      alpha = alpha + 1;
    }
  return (CLEAN);
}

int		draw_sky_grd(t_system *sys)
{
  int		rank;
  char		color[4];
  int		fd;

  get_color(sys, SKY, sys->sky_grd.edn, &color[0]);
  rank = 0;
  while (rank < sys->sky_grd.wdth * sys->sky_grd.hght / 2)
    {
      sys->sky_grd.dat[rank] = color[rank % 4];
      rank++;
    }
  get_color(sys, GROUND, sys->sky_grd.edn, &color[0]);
  while (rank < sys->sky_grd.wdth * sys->sky_grd.hght)
    {
      sys->sky_grd.dat[rank] = color[rank % 4];
      rank++;
    }
  return (CLEAN);
}

int	init_img(t_image *img, void *mlx)
{
  int           bpp;
  int           endian;
  int           width;

  img->img = mlx_new_image(mlx, 640, 640);
  img->dat = mlx_get_data_addr(img->img, &bpp, &width, &endian);
  img->bpp = bpp;
  img->edn = endian;
  img->wdth = width;
  img->hght = 640 * 640 * (bpp / 8) / img->wdth;
  return (CLEAN);
}

int		init_sys_img(t_system *sys)
{
  init_img(&(sys->sky_grd), sys->mlx);
  draw_sky_grd(sys);
  init_img(&(sys->walls), sys->mlx);
  init_walls(sys);
  init_img(&(sys->fnl_img), sys->mlx);
  return (CLEAN);
}

int	get_final_img(t_system *sys)
{
  int	rank;
  int	i;

  rank = 0;
  while (rank < 640 * 640 * 4)
    {
      i = -1;
      if (sys->walls.dat[rank + (sys->fnl_img.edn - 1) * -3] == 255)
	{
	  while (++i < 4)
	    sys->fnl_img.dat[rank + i] = sys->sky_grd.dat[rank + i];
	}
      else
	{
	  while (++i < 4)
	    sys->fnl_img.dat[rank + i] = sys->walls.dat[rank + i];
	}
      rank = rank + i;
    }
  mini_map_display(sys);
  if (sys->game == SOK)
    display_cursor(sys);
  return (CLEAN);
}
