/*
** sokoban.c for the sokoban game in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Dec 18 18:09:19 2014 quentin gasparotto
** Last update Sun Dec 21 10:28:38 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"
#include <math.h>

int	block_transition(char *act_block, char *dest_block)
{
  if (*act_block == 'B')
    {
      *act_block = '0';
      if (*dest_block == 'F')
	*dest_block = 'P';
      else
	*dest_block = 'B';
    }
  else if (*act_block == 'P')
    {
      *act_block = 'F';
      if (*dest_block == 'F')
	*dest_block = 'P';
      else
	*dest_block = 'B';
    }
  return (CLEAN);
}

int	horizontal_collision(t_system *sys, t_point2d block, int side)
{
  if (side == WEST)
    {
      if (sys->field->char_field[(int)block.y][(int)block.x - 1] != '1')
	{
	  block_transition(&sys->field->char_field[(int)block.y][(int)block.x],
			   &sys->field->char_field[(int)block.y][(int)block.x - 1]);
	}
    }
  else if (side == EAST)
    {
      if (sys->field->char_field[(int)block.y][(int)block.x + 1] != '1')
	{
	  block_transition(&sys->field->char_field[(int)block.y][(int)block.x],
			   &sys->field->char_field[(int)block.y][(int)block.x + 1]);
	}
    }
  return (CLEAN);
}

int	vertical_collision(t_system *sys, t_point2d block, int side)
{
  if (side == NORTH)
    {
      if (sys->field->char_field[(int)block.y + 1][(int)block.x] != '1')
        {
	  block_transition(&sys->field->char_field[(int)block.y][(int)block.x],
			   &sys->field->char_field[(int)block.y + 1][(int)block.x]);
        }
    }
  else if (side == SOUTH)
    {
      if (sys->field->char_field[(int)block.y - 1][(int)block.x] != '1')
        {
	  block_transition(&sys->field->char_field[(int)block.y][(int)block.x],
			   &sys->field->char_field[(int)block.y - 1][(int)block.x]);
        }
    }
  return (CLEAN);
}

int	block_collision(t_system *sys, t_point2d block, int side)
{
  if ((side == SOUTH && block.y - 1 >= 0) ||
      (side == NORTH && block.y + 1 < sys->field->height))
    {
      vertical_collision(sys, block, side);
    }
  else if ((side == WEST && block.x - 1 >= 0) ||
	   (side == EAST && block.x + 1 < sys->field->width))
    {
      horizontal_collision(sys, block, side);
    }
  return (CLEAN);
}

int		sokoban(t_system *sys)
{
  t_streight	frnt;
  int		k;
  int		side;

  frnt.vec.x = cos(sys->alpha * M_PI / 180.0);
  frnt.vec.y = sin(sys->alpha * M_PI / 180.0);
  k = 100;
  frnt.result = search_walls(sys, frnt.vec, -1, &k);
  sys->bk = 'B';
  side = get_side(sys, k, frnt);
  if (sys->field->char_field[(int)frnt.result.y][(int)frnt.result.x] == 'B')
    {
      block_collision(sys, frnt.result, side);
      if (sokoban_win(sys) != END)
	return (get_view(sys, sys->field, sys->alpha * M_PI / 180.0));
      return (END);
    }
  sys->bk = 'P';
  side = get_side(sys, k, frnt);
  if (sys->field->char_field[(int)frnt.result.y][(int)frnt.result.x] == 'P')
    {
      block_collision(sys, frnt.result, side);
      return (get_view(sys, sys->field, sys->alpha * M_PI / 180.0));
    }
}
