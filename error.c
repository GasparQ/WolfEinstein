/*
** error.c for error gestion in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Sat Dec 13 12:06:25 2014 quentin gasparotto
** Last update Fri Dec 19 15:39:08 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"

int	my_strerror(int error)
{
  if (error == FLD_ERR)
    write(2, "Error when loading the field\n", 29);
  else if (error == MLX_FAIL)
    write(2, "Error when loading mlx\n", 23);
  else if (error == WDW_FAIL)
    write(2, "Error when loadin the window\n", 29);
  else if (error == BAD_FLD)
    write(2, "You attempt to load a bad field\n", 32);
  else if (error == BAD_FD)
    write(2, ": No such file\n", 15);
  else if (error == TEXT_ERR)
    write(2, "Error when loading textures\n", 28);
  else if (error == MALLOC_ERR)
    write(2, "Malloc fail\n", 12);
  else if (error == ENV_ERR)
    write(2, "Environement fail\n", 18);
  return (ERROR);
}

int	is_in_str(char act_char, char *ref_str)
{
  int	rank;

  rank = 0;
  while (ref_str[rank] != '\0')
    {
      if (ref_str[rank] == act_char)
	return (YES);
      rank = rank + 1;
    }
  return (NO);
}

int	check_field(t_field *field)
{
  int	line;
  int	column;

  line = 0;
  while (line < field->height)
    {
      column = 0;
      while (field->char_field[line][column] != '\0')
	{
	  if (is_in_str(field->char_field[line][column], "01SEIOBFP\n") == NO)
	    {
	      free_my_field(field);
	      return (my_strerror(BAD_FLD));
	    }
	  column = column + 1;
	}
      line = line + 1;
    }
  return (CLEAN);
}
