/*
** get_side.c for function to know the orientation of a wall in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Sat Dec 13 10:42:40 2014 quentin gasparotto
** Last update Sat Dec 20 14:28:03 2014 quentin gasparotto
*/

#include <math.h>
#include "./include/wolf.h"
#include "./include/minilibx_objects.h"

double		get_angle(t_system *sys, t_point2d fld_ind)
{
  t_point2d     vector;

  if (sys->pos.x >= ((int)fld_ind.x + 1) * 100.0)
    {
      vector.x = ((int)fld_ind.x + 1) * 100.0 - sys->pos.x;
      if (sys->pos.y >= ((int)fld_ind.y + 1) * 100.0)
        vector.y = ((int)fld_ind.y + 1) * 100 - sys->pos.y;
      else
        vector.y = (int)fld_ind.y * 100.0 - sys->pos.y;
    }
  else
    {
      vector.x = (int)fld_ind.x * 100.0 - sys->pos.x;
      if (sys->pos.y <= (int)fld_ind.y * 100.0)
        vector.y = (int)fld_ind.y * 100.0 - sys->pos.y;
      else
        vector.y = ((int)fld_ind.y + 1) * 100.0 - sys->pos.y;
    }
  return (atan(vector.y / vector.x));
}

int		check_left(t_system *sys, t_point2d bef_vec,
			   t_point2d fld_ind, double angle)
{
  double        ref_angle;

  ref_angle = get_angle(sys, fld_ind);
  if ((int)bef_vec.x == (int)fld_ind.x - 1 &&
      sys->field->char_field[(int)fld_ind.y][(int)fld_ind.x - 1] != sys->bk)
    {
      if ((int)bef_vec.y == (int)fld_ind.y - 1 &&
          sys->field->char_field[(int)fld_ind.y - 1][(int)fld_ind.x] != sys->bk)
        {
          if (angle > ref_angle)
            return (EAST);
          else
            return (NORTH);
        }
      if ((int)bef_vec.y == (int)fld_ind.y + 1 &&
          sys->field->char_field[(int)fld_ind.y + 1][(int)fld_ind.x] != sys->bk)
        {
          if (angle > ref_angle)
            return (SOUTH);
          else
            return (EAST);
	}
    }
  return (0);
}

int		check_right(t_system *sys, t_point2d bef_vec,
			    t_point2d fld_ind, double angle)
{
  double	ref_angle;

  ref_angle = get_angle(sys, fld_ind);
  if ((int)bef_vec.x == (int)fld_ind.x + 1 &&
      sys->field->char_field[(int)fld_ind.y][(int)fld_ind.x + 1] != sys->bk)
    {
      if ((int)bef_vec.y == (int)fld_ind.y - 1 &&
          sys->field->char_field[(int)fld_ind.y - 1][(int)fld_ind.x] != sys->bk)
        {
          if (angle > ref_angle)
            return (NORTH);
          else
            return (WEST);
        }
      if ((int)bef_vec.y == (int)fld_ind.y + 1 &&
          sys->field->char_field[(int)fld_ind.y + 1][(int)fld_ind.x] != sys->bk)
        {
          if (angle > ref_angle)
            return (WEST);
          else
            return (SOUTH);
        }
    }
  return (0);
}

int	check_front(t_system *sys, t_point2d bef_vec, t_point2d fld_ind)
{
  if ((int)bef_vec.x == (int)fld_ind.x - 1 &&
      sys->field->char_field[(int)fld_ind.y][(int)fld_ind.x - 1] != sys->bk)
    return (EAST);
  else if ((int)bef_vec.x == (int)fld_ind.x + 1 &&
    sys->field->char_field[(int)fld_ind.y][(int)fld_ind.x + 1] != sys->bk)
    return (WEST);
  else if ((int)bef_vec.y == (int)fld_ind.y - 1 &&
    sys->field->char_field[(int)fld_ind.y - 1][(int)fld_ind.x] != sys->bk)
    return (NORTH);
  else if ((int)bef_vec.y == (int)fld_ind.y + 1 &&
	   sys->field->char_field[(int)fld_ind.y + 1][(int)fld_ind.x] != sys->bk)
    return (SOUTH);
  else
    return (BLACK);
}

int		get_side(t_system *sys, int k, t_streight streight)
{
  t_point2d     bef_vec;
  int		side;
  double	angle;

  bef_vec.x = (sys->pos.x + (streight.vec.x / 100) * k) / 100.0;
  bef_vec.y = (sys->pos.y + (streight.vec.y / 100) * k) / 100.0;
  while (k >= 0)
    {
      bef_vec.x = (sys->pos.x + (streight.vec.x / 100) * k) / 100.0;
      bef_vec.y = (sys->pos.y + (streight.vec.y / 100) * k) / 100.0;
      if (sys->field->char_field[(int)bef_vec.y][(int)bef_vec.x] != sys->bk)
        k = 0;
      k = k - 1;
    }
  angle = atan(streight.vec.y / streight.vec.x);
  side = check_left(sys, bef_vec, streight.result, angle);
  if (side == 0)
    side = check_right(sys, bef_vec, streight.result, angle);
  if (side == 0)
    side = check_front(sys, bef_vec, streight.result);
  return (side);
}
