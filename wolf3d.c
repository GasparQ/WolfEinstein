/*
** wolf3d.c for wolf 3d main function in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Dec  2 13:34:59 2014 quentin gasparotto
** Last update Sat Dec 20 14:43:00 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include <mlx.h>
#include <math.h>

int	load(t_system *sys, char *file)
{
  if ((sys->field = get_field(file)) == NULL)
    return (my_strerror(FLD_ERR));
  if (check_field(sys->field) == ERROR)
    return (ERROR);
  sys->wdw = mlx_new_window(sys->mlx, 640, 640, "WOLF 3D");
  if (sys->wdw == NULL)
    return (my_strerror(WDW_FAIL));
  init_sys_img(sys);
  sys->game = OFF;
  home(sys);
  return (CLEAN);
}

int		main(int argc, char **argv, char **env)
{
  t_system	sys;

  if (env[0] == NULL)
    return (my_strerror(ENV_ERR));
  if ((sys.mlx = mlx_init()) == NULL)
    return (ERROR);
  if (argc > 1)
    {
      if (load(&sys, argv[1]) == ERROR)
	return (ERROR);
    }
  else
    {
      if (load(&sys, "laby/basic.wlf") == ERROR)
	return (ERROR);
    }
  mlx_mouse_hook(sys.wdw, &mouse_gestion, &sys);
  mlx_expose_hook(sys.wdw, &expose_gestion, &sys);
  mlx_hook(sys.wdw, KeyPress, KeyPressMask, &keyboard_gestion, &sys);
  mlx_loop(sys.mlx);
  return (CLEAN);
}
