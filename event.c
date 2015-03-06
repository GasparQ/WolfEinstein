/*
** event.c for event functions file in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Dec  2 14:49:32 2014 quentin gasparotto
** Last update Sun Dec 21 10:31:09 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include <math.h>
#include <mlx.h>

int	mouse_gestion(int button, int x, int y, t_system *sys)
{
  if (button == 3 && sys->game == SOK)
    {
      sokoban(sys);
      display_cursor(sys);
    }
  return (CLEAN);
}

int	expose_gestion(t_system *sys)
{
  mlx_put_image_to_window(sys->mlx, sys->wdw, sys->fnl_img.img, 0, 0);
  if (sys->game == HOME)
    home(sys);
  return (CLEAN);
}

int	player_view(int keycode, t_system *sys)
{
  if (keycode == UP || keycode == 'z')
    {
      if (walk_collision(sys, 1) == END)
	return (END);
    }
  if (keycode == DOWN || keycode == 's')
    {
      if (walk_collision(sys, -1) == END)
	return (END);
    }
  if (keycode == RIGHT || keycode == 'd')
    sys->alpha = (int)(sys->alpha - 5) % 360;
  if (keycode == LEFT || keycode == 'q')
    sys->alpha = (int)(sys->alpha + 5) % 360;
  get_view(sys, sys->field, (sys->alpha / 360) * 2 * M_PI);
  return (CLEAN);
}

int	keyboard_gestion(int keycode, t_system *sys)
{
  if (keycode == ESCAPE)
    {
      mlx_destroy_window(sys->mlx, sys->wdw);
      free_my_field(sys->field);
      free(sys->mlx);
      exit(CLEARLY);
    }
  else if (keycode == RETURN && sys->game == OFF)
    home(sys);
  else if (sys->game == HOME)
    home_gestion(keycode, sys);
  else if (sys->game == ON || sys->game == SOK)
    return (player_view(keycode, sys));
  return (CLEAN);
}
