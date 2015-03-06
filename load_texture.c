/*
** load_texture.c for function to load texture in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Dec 15 10:30:32 2014 quentin gasparotto
** Last update Thu Dec 18 12:24:55 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/get_next_line.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

int	extract_nbr(char *str, int *var)
{
  int	rank;
  int	ret;
  int	coeff;

  ret = 0;
  while (str[ret] != '\0' && str[ret] > 47 && str[ret] < 58)
    ret = ret + 1;
  rank = ret - 1;
  coeff = 1;
  *var = 0;
  while (rank >= 0)
    {
      *var = *var + (str[rank] - 48) * coeff;
      coeff = coeff * 10;
      rank = rank - 1;
    }
  return (ret + 2);
}

int	create_img(t_system *sys, t_image *ig, char *dim_line)
{
  int	width;
  int	height;
  int	rank;

  rank = extract_nbr(&dim_line[1], &width);
  rank = rank + extract_nbr(&dim_line[rank], &height);
  extract_nbr(&dim_line[rank - 1], &rank);
  return (rank);
}

int	search_col(char act_char, int *color_tab)
{
  int	rank;

  rank = 0;
  while (color_tab[rank] != 0)
    {
      if (act_char == (color_tab[rank] >> 24) % 256)
	return (rank);
      rank = rank + 1;
    }
  return (0);
}

int	load_img(t_image *img, const int fd, int *color_tab)
{
  int	rank;
  int	act_line;
  int	act_col;
  int	data_rank;
  char	*line;

  act_line = 0;
  data_rank = 0;
  while (act_line < img->hght)
    {
      line = get_next_line(fd);
      rank = 1;
      while (line[rank] != '"' && line[rank] != '\0')
	{
	  act_col = search_col(line[rank], color_tab);
	  img->dat[data_rank++] = color_tab[act_col] % 256;
	  img->dat[data_rank++] = (color_tab[act_col] >> 8) % 256;
	  img->dat[data_rank++] = (color_tab[act_col] >> 16) % 256;
	  img->dat[data_rank++] = 0;
	  rank++;
	}
      free(line);
      act_line = act_line + 1;
    }
  return (0);
}

int		load_texture(const int fd, t_system *sys, t_image *text_img)
{
  int		rank;
  char		*line;
  int		*color_tab;
  int		color_nb;

  rank = 0;
  while (rank < 4)
    {
      line = get_next_line(fd);
      if (rank != 3)
	free(line);
      rank = rank + 1;
    }
  color_nb = create_img(sys, text_img, line) + 1;
  free(line);
  if ((color_tab = malloc(sizeof(int) * color_nb)) == NULL)
    return (0);
  color_tab[color_nb - 1] = 0;
  init_color_tab(fd, color_tab, color_nb);
  line = get_next_line(fd);
  free(line);
  load_img(text_img, fd, color_tab);
  free(color_tab);
  return (0);
}
