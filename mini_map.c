/*
** mini_map.c for mini map display in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Dec 18 12:31:02 2014 quentin gasparotto
** Last update Sat Dec 20 09:59:43 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/wolf.h"

int		mini_map_border(t_system *sys)
{
  t_point2d	pix;
  unsigned char	color[4];

  pix.y = HEIGHT - 105;
  while (pix.y < HEIGHT - 5)
    {
      pix.x = WIDTH - 106;
      if (pix.y < HEIGHT - 100 || pix.y > HEIGHT - 11)
	{
	  while (++pix.x < WIDTH - 5)
	    put_pix_to_img(sys, &(sys->fnl_img), pix, BLACK);
	}
      else
	{
	  while (++pix.x < WIDTH - 100)
	    put_pix_to_img(sys, &(sys->fnl_img), pix, BLACK);
	  pix.x = WIDTH - 11;
	  while (++pix.x < WIDTH - 5)
	    put_pix_to_img(sys, &(sys->fnl_img), pix, BLACK);
	}
      pix.y = pix.y + 1;
    }
  return (CLEAN);
}

int		draw_square(t_system *sys, t_point2d id, t_point2d start, int color)
{
  t_point2d	pix;
  t_point2d	conv;
  int		coord;
  int		rank;

  pix.y = HEIGHT - 100;
  while (pix.y < HEIGHT - 90)
    {
      pix.x = WIDTH - 100;
      while (pix.x < WIDTH - 90)
	{
	  conv.x = (int)id.x * 10 + pix.x;
	  conv.y = (int)id.y * 10 + pix.y;
	  put_pix_to_img(sys, &(sys->fnl_img), conv, color);
	  pix.x = pix.x + 1;
	}
      pix.y = pix.y + 1;
    }
  return (CLEAN);
}

int		choose_block(t_system *sys, int x, int y, t_point2d start)
{
  int		color;
  t_point2d	id;

  color = GREY;
  if (sys->field->char_field[y][x] == '1')
    color = SOUTH;
  else if (sys->field->char_field[y][x] == 'I')
    color = INPORT;
  else if (sys->field->char_field[y][x] == 'E')
    color = WIN;
  else if (sys->field->char_field[y][x] == 'B')
    color = BLOCK;
  else if (sys->field->char_field[y][x] == 'P')
    color = PLACED;
  else if (sys->field->char_field[y][x] == 'F')
    color = FINISH;
  id.x = x - start.x;
  id.y = y - start.y;
  draw_square(sys, id, start, color);
  return (CLEAN);
}

t_point2d	get_start(t_system *sys)
{
  t_point2d	start;

  start.x = (int)sys->pos.x / 100 - 5;
  if (start.x < 0)
    start.x = 0;
  else if (start.x > sys->field->width - 9)
    start.x = sys->field->width - 9;
  start.y = (int)sys->pos.y / 100 - 5;
  if (start.y < 0)
    start.y = 0;
  else if (start.y > sys->field->height - 9)
    start.y = sys->field->height - 9;
  return (start);
}

int		mini_map_display(t_system *sys)
{
  t_point2d	id;
  t_point2d     map_pos;
  t_point2d	start;
  int		coord;

  start = get_start(sys);
  id.y = 0;
  while (start.y + id.y < sys->field->height && id.y < 9)
    {
      id.x = 0;
      while (start.x + id.x < sys->field->width && id.x < 9)
	{
	  choose_block(sys, start.x + id.x, start.y + id.y, start);
	  id.x = id.x + 1;
	}
      id.y = id.y + 1;
    }
  map_pos.x = sys->pos.x / 100.0 - start.x;
  map_pos.y = sys->pos.y / 100.0 - start.y;
  draw_square(sys, map_pos, start, PLAY);
  mini_map_border(sys);
  return (CLEAN);
}
