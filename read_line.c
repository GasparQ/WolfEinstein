/*
** read_line.c for read_line function for get next line in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Dec 11 13:25:50 2014 quentin gasparotto
** Last update Mon Dec 15 16:52:04 2014 quentin gasparotto
*/

#include <stdlib.h>
#include <unistd.h>
#include "./include/get_next_line.h"

char	*make_transition(char *char_read, char *read_line, int rank, int size)
{
  int   rank_stat;
  int   rank_read;
  char  *line;

  size = size + rank;
  if ((line = malloc(size)) == NULL)
    {
      write(2, "Can't alloc\n", 12);
      return (NULL);
    }
  rank_stat = -1;
  while (read_line[++rank_stat] != '\0' && rank_stat < size)
    line[rank_stat] = read_line[rank_stat];
  rank_read = -1;
  while (char_read[++rank_read] != '\n' && rank_stat + rank_read < size - 1)
    line[rank_stat + rank_read] = char_read[rank_read];
  line[rank_stat + rank_read] = '\0';
  rank_stat = 0;
  while (char_read[rank + rank_stat] != '\0')
    {
      read_line[rank_stat] = char_read[rank + rank_stat];
      rank_stat++;
    }
  read_line[rank_stat] = '\0';
  return (line);
}

char	*no_read(char *read_line)
{
  char  *line;
  int   rank;

  line = NULL;
  if (read_line[0] != '\0')
    {
      rank = -1;
      while (read_line[++rank] != '\0');
      if ((line = malloc(rank + 1)) == NULL)
        {
          write(2, "Can't alloc\n", 12);
          return (NULL);
        }
      line[rank] = '\0';
      rank = 0;
      while (read_line[rank] != '\0')
        {
          line[rank] = read_line[rank];
          rank++;
        }
      read_line[0] = '\0';
    }
  return (line);
}

char	*smthg_read(char **str_tab, int rank_read, int size, int *nb_read)
{
  int   rank;
  char  *line;

  line = NULL;
  str_tab[0][rank_read * (*nb_read)] = '\0';
  rank = 0;
  while (str_tab[0][rank] != '\n' && str_tab[0][rank] != '\0')
    rank++;
  if (str_tab[0][rank] == '\0' && rank == LINE_LEN * (*nb_read))
    {
      (*nb_read)++;
      str_tab[0] = my_realloc_str(str_tab[0], LINE_LEN * (*nb_read) + 1);
    }
  else
    {
      line = make_transition(str_tab[0], str_tab[1], ++rank, size);
      *nb_read = 0;
    }
  return (line);
}

char	*condition(const int fd, char **str_tab, int *nb_read, int size)
{
  int   rank_read;
  char  *line;

  rank_read = 0;
  if ((rank_read = read(fd, str_tab[0], LINE_LEN)) > 0)
    line = smthg_read(str_tab, rank_read, size, nb_read);
  else if (rank_read == -1)
    {
      write(2, "Bad file descriptor\n", 20);
      *nb_read = 0;
      return (NULL);
    }
  else
    {
      line = no_read(str_tab[1]);
      *nb_read = 0;
    }
  return (line);
}

char	*read_line(const int fd, char *read_line, int size)
{
  char  *char_read;
  char  *str_tab[2];
  char  *line;
  int   nb_read;

  line = NULL;
  if ((char_read = malloc(LINE_LEN + 1)) == NULL)
    return (0);
  init_buffer(char_read, LINE_LEN + 1);
  nb_read = 1;
  str_tab[0] = char_read;
  str_tab[1] = read_line;
  while (nb_read != 0)
    line = condition(fd, &(str_tab[0]), &nb_read, size);
  free(char_read);
  return (line);
}
