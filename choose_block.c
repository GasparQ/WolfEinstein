/*
** choose_block.c for choose block function in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Fri Dec 19 14:54:01 2014 quentin gasparotto
** Last update Sat Dec 20 14:26:06 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"

int	disp_block(t_system *sys, t_streight streight, int x, int k)
{
  int		blck;
  int		len;

  blck = sys->field->char_field[(int)streight.result.y][(int)streight.result.x];
  if (blck == '0')
    return (0);
  else
    {
      len = (int)(320.0 / k * 100.0);
      sys->bk = '1';
      if (blck == '1')
	return (display_walls(sys, x, len, get_side(sys, k, streight)));
      else if (blck == 'I')
	return (display_walls(sys, x, len, INPORT));
      else if (blck == 'E')
	return (display_walls(sys, x, len, WIN));
      else if (blck == 'B')
	return (display_walls(sys, x, len, BLOCK));
      else if (blck == 'P')
	return (display_walls(sys, x, len, PLACED));
      else if (blck == 'F')
	return (display_walls(sys, x, len, FINISH));
    }
}
