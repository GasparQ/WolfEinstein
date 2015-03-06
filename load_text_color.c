/*
** load_text_color.c for function to load colors of a texture in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Dec 15 16:16:19 2014 quentin gasparotto
** Last update Wed Dec 17 15:36:12 2014 quentin gasparotto
*/

#include "./include/minilibx_objects.h"
#include "./include/get_next_line.h"
#include "./include/wolf.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

int	search_char(char act_char, char *base)
{
  int   rank;

  rank = 0;
  while (base[rank] != '\0')
    {
      if (base[rank] == act_char)
        return (rank);
      rank = rank + 1;
    }
  return (-1);
}

int	init_hex_bs(char *base)
{
  int   rank;

  rank = 0;
  base[0] = '0';
  base[1] = '1';
  base[2] = '2';
  base[3] = '3';
  base[4] = '4';
  base[5] = '5';
  base[6] = '6';
  base[7] = '7';
  base[8] = '8';
  base[9] = '9';
  base[10] = 'A';
  base[11] = 'B';
  base[12] = 'C';
  base[13] = 'D';
  base[14] = 'E';
  base[15] = 'F';
  base[16] = '\0';
  return (0);
}

int	conv_hex(char c)
{
  int   nbr;

  nbr = 0;
  nbr = c % 16;
  nbr = nbr + (c / 16 % 16) * 10;
  return (nbr);
}

int	init_color_tab(const int fd, unsigned int *col_tab, int color_nb)
{
  char  *line;
  int   rk;
  int   my_char;
  char  base[17];

  init_hex_bs(&base[0]);
  line = get_next_line(fd);
  free(line);
  rk = 0;
  while (rk < color_nb - 1)
    {
      line = get_next_line(fd);
      my_char = conv_hex(line[1]);
      col_tab[rk] = my_char / 10 % 10 * pow(16, 7) + my_char % 10 * pow(16, 6);
      col_tab[rk] = col_tab[rk] + search_char(line[6], base) * pow(16, 5);
      col_tab[rk] = col_tab[rk] + search_char(line[7], base) * pow(16, 4);
      col_tab[rk] = col_tab[rk] + search_char(line[8], base) * pow(16, 3);
      col_tab[rk] = col_tab[rk] + search_char(line[9], base) * pow(16, 2);
      col_tab[rk] = col_tab[rk] + search_char(line[10], base) * 16;
      col_tab[rk] = col_tab[rk] + search_char(line[11], base);
      free(line);
      rk = rk + 1;
    }
  return (0);
}
