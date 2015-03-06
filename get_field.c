/*
** get_field.c for get field from file  in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Tue Dec  2 16:53:27 2014 quentin gasparotto
** Last update Sat Dec 13 14:57:12 2014 quentin gasparotto
*/

#include "./include/get_next_line.h"
#include "./include/minilibx_objects.h"
#include "./include/my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int	get_height(const int fd, t_field *field)
{
  char	*line;

  field->height = 0;
  while ((line = get_next_line(fd)) != NULL)
    {
      field->height++;
      free(line);
    }
  return (CLEAN);
}

t_field	*err_field(int err, void *ptr)
{
  if (err == WRG_HGT)
    free(ptr);
  else if (err == EPTY)
    free_my_field(ptr);
  else if (err == BAD_FD)
    {
      my_putstr(ptr);
      my_strerror(BAD_FD);
    }
  return (NULL);
}

t_field		*get_field(char *pathname)
{
  t_field	*field;
  int		fd;
  int		rank;

  if ((fd = open(pathname, O_RDONLY)) == -1)
    return (err_field(BAD_FD, pathname));
  if ((field = malloc(sizeof(*field))) == NULL)
    return (NULL);
  get_height(fd, field);
  if (field->height == 0)
    return (err_field(WRG_HGT, field));
  if ((field->char_field = malloc(sizeof(char *) * field->height)) == NULL)
    return (NULL);
  lseek(fd, 0, SEEK_SET);
  rank = 0;
  if ((field->char_field[rank] = get_next_line(fd)) == NULL)
    return (err_field(EPTY, field));
  while (rank < field->height - 1)
    field->char_field[++rank] = get_next_line(fd);
  field->width = my_strlen(field->char_field[0]);
  close(fd);
  return (field);
}

int	free_my_field(t_field *field)
{
  int	rank;

  rank = 0;
  while (rank < field->height)
    {
      free(field->char_field[rank]);
      rank++;
    }
  free(field->char_field);
  free(field);
  return (CLEAN);
}
