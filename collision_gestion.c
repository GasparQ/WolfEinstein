/*
** collision_gestion.c for collision with walls in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Sun Dec 14 12:37:34 2014 quentin gasparotto
** Last update Sat Dec 20 14:54:31 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	you_won(t_system *sys)
{
  int	fd;

  if ((fd = open("./texture/win.xpm", O_RDONLY)) == -1)
    return (my_strerror(BAD_FD));
  load_texture(fd, sys, &(sys->fnl_img));
  mlx_put_image_to_window(sys->mlx, sys->wdw, sys->fnl_img.img, 0, 0);
  sys->game = OFF;
  close(fd);
  return (END);
}

int	out_of_field(t_system *sys, int coeff)
{
  if ((int)sys->pos.x / 100 >= sys->field->width || sys->pos.x < 0)
    {
      sys->pos.x = sys->pos.x - coeff * 15 * cos(sys->alpha * M_PI / 180.0);
    }
  if ((int)sys->pos.y / 100 >= sys->field->height || sys->pos.y < 0)
    {
      sys->pos.y = sys->pos.y - coeff * 15 * sin(sys->alpha * M_PI / 180.0);
    }
  return (CLEAN);
}

int	into_walls(t_system *sys, int coeff)
{
  int	x;
  int	y;

  sys->pos.x = sys->pos.x + coeff * 15 * cos(sys->alpha * M_PI / 180.0);
  x = (int)sys->pos.x / 100;
  y = (int)sys->pos.y / 100;
  if (sys->field->char_field[y][x] == '1' ||
      sys->field->char_field[y][x] == 'B' ||
      sys->field->char_field[y][x] == 'P')
    {
      sys->pos.x = sys->pos.x - coeff * 15 * cos(sys->alpha * M_PI / 180.0);
    }
  sys->pos.y = sys->pos.y + coeff * 15 * sin(sys->alpha * M_PI / 180.0);
  x = (int)sys->pos.x / 100;
  y = (int)sys->pos.y / 100;
  if (sys->field->char_field[y][x] == '1' ||
      sys->field->char_field[y][x] == 'B' ||
      sys->field->char_field[y][x] == 'P')
    {
      sys->pos.y = sys->pos.y - coeff * 15 * sin(sys->alpha * M_PI / 180.0);
    }
  return (CLEAN);
}

int	sokoban_win(t_system *sys)
{
  int	row;
  int	column;

  row = 0;
  while (row < sys->field->height)
    {
      column = 0;
      while (column < sys->field->width)
	{
	  if (sys->field->char_field[row][column] == 'B')
	    return (CLEAN);
	  column = column + 1;
	}
      row = row + 1;
    }
  return (you_won(sys));
}

int	walk_collision(t_system *sys, int coeff)
{
  int	x;
  int	y;

  into_walls(sys, coeff);
  out_of_field(sys, coeff);
  x = (int)sys->pos.x / 100;
  y = (int)sys->pos.y / 100;
  if (sys->field->char_field[y][x] == 'I')
    get_pos(sys, 'O');
  else if (sys->field->char_field[y][x] == 'E')
    return (you_won(sys));
  return (CLEAN);
}
