/*
** get_next_line.c for get next line in /home/gaspar_q/rendu/CPE_2014_get_next_line
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Nov 17 15:19:33 2014 quentin gasparotto
** Last update Sat Dec 13 13:41:00 2014 quentin gasparotto
*/

#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include "./include/get_next_line.h"

char	*my_realloc_str(char *ptr, int size)
{
  char  *new_ptr;
  int   rank;

  if ((new_ptr = malloc(size)) == NULL)
    return (NULL);
  rank = 0;
  while (rank < size)
    new_ptr[rank++] = '\0';
  if (ptr != NULL)
    {
      rank = -1;
      while (ptr[++rank] != '\0')
        new_ptr[rank] = ptr[rank];
      new_ptr[rank] = '\0';
      free(ptr);
    }
  return (new_ptr);
}

int	init_buffer(char *buffer, int size)
{
  int   rank;

  rank = 0;
  while (rank < size)
    buffer[rank++] = '\0';
  return (0);
}

char	*new_line_stat(char *unret_char, int size)
{
  char	*line;
  int	rank;
  int	rank_stat;

  if ((line = malloc(size + 1)) == NULL)
    {
      write(2, "Can't alloc\n", 12);
      return (NULL);
    }
  rank = -1;
  while (unret_char[++rank] != '\n')
    line[rank] = unret_char[rank];
  line[rank++] = '\0';
  rank_stat = 0;
  while (unret_char[rank + rank_stat] != '\0')
    {
      unret_char[rank_stat] = unret_char[rank + rank_stat];
      rank_stat++;
    }
  unret_char[rank_stat] = '\0';
  return (line);
}

char		*get_next_line(const int fd)
{
  static char	unret_char[LINE_LEN];
  static int	temoin = 0;
  char		*line;
  int		size;

  size = 0;
  line = NULL;
  if (temoin == 0)
    init_buffer(&unret_char[0], LINE_LEN);
  while (unret_char[size] != '\0' && unret_char[size] != '\n')
    size++;
  temoin++;
  if (unret_char[size] == '\0')
    line = read_line(fd, &unret_char[0], size);
  else if (unret_char[size] == '\n')
    {
      if ((line = new_line_stat((&unret_char[0]), size)) == NULL)
	return (NULL);
    }
  return (line);
}
