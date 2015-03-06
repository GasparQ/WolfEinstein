/*
** my_put_char.c for my_put_char in /home/gaspar_q/rendu/Piscine_C_J03
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Wed Oct  1 15:36:15 2014 quentin gasparotto
** Last update Sun Dec 14 12:08:38 2014 quentin gasparotto
*/

#include <unistd.h>

int	my_putchar(char c)
{
  write(1, &c, 1);
}
