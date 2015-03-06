/*
** my_putstr.c for my_putstr in /home/gaspar_q/rendu/Piscine_C_J04
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Thu Oct  2 10:35:12 2014 quentin gasparotto
** Last update Thu Dec 18 18:32:42 2014 quentin gasparotto
*/

#include <stdlib.h>

int	my_putstr(char *str)
{
  int	i;

  i = 0;
  if (str != NULL)
    {
      while (str[i] != '\0')
	{
	  my_putchar(str[i]);
	  i = i + 1;
	}
    }
  else
    {
      my_putstr("No result");
    }
  return (0);
}
