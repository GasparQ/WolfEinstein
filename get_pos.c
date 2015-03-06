/*
** get_strt_pos.c for file where I define the start position in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Sat Dec 13 14:49:35 2014 quentin gasparotto
** Last update Tue Dec 16 18:24:10 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"

int	get_pos(t_system *sys, char out_pos)
{
  int	line;
  int	column;

  line = 0;
  while (line < sys->field->height)
    {
      column = 0;
      while (sys->field->char_field[line][column] != '\0')
	{
	  if (sys->field->char_field[line][column] == out_pos)
	    {
	      sys->pos.x = column * 100.0 + 50.0;
	      sys->pos.y = line * 100.0 + 50.0;
	      return (CLEAN);
	    }
	  column = column + 1;
	}
      line = line + 1;
    }
  sys->pos.x = 50;
  sys->pos.y = 50;
  return (CLEAN);
}
