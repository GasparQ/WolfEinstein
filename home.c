/*
** home.c for home in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Dec 18 09:53:16 2014 quentin gasparotto
** Last update Sun Dec 21 10:45:03 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int	load_game(t_system *sys)
{
  if (sys->pos.y == 300)
    {
      sys->game = ON;
    }
  else if (sys->pos.y == 350)
    {
      sys->game = SOK;
    }
  else
    {
      return (home(sys));
    }
  sys->alpha = 45;
  get_pos(sys, 'S');
  get_view(sys, sys->field, sys->alpha * M_PI / 180.0);
  return (CLEAN);
}

int	home_gestion(int keycode, t_system *sys)
{
  if (keycode == UP)
    {
      if (sys->pos.y > 300)
        sys->pos.y = sys->pos.y - 50;
      else
        sys->pos.y = 400;
    }
  else if (keycode == DOWN)
    {
      if (sys->pos.y < 400)
        sys->pos.y = sys->pos.y + 50;
      else
        sys->pos.y = 300;
    }
  else if (keycode == RETURN)
    {
      return (load_game(sys));
    }
  return (home(sys));
}

int	home(t_system *sys)
{
  int	fd;

  if (sys->game == OFF)
    {
      if ((fd = open("./texture/home.xpm", O_RDONLY)) == -1)
	return (my_strerror(BAD_FD));
      sys->game = HOME;
      sys->pos.y = 300;
      load_texture(fd, sys, &(sys->fnl_img));
      close(fd);
    }
  mlx_put_image_to_window(sys->mlx, sys->wdw, sys->fnl_img.img, 0, 0);
  mlx_string_put(sys->mlx, sys->wdw, 250, 300, RED, "Labyrinthe");
  mlx_string_put(sys->mlx, sys->wdw, 250, 350, RED, "Sokoban");
  mlx_string_put(sys->mlx, sys->wdw, 250, 400, RED, "Pointless Button");
  mlx_string_put(sys->mlx, sys->wdw, 220, sys->pos.y, RED, "->");
  return (CLEAN);
}
