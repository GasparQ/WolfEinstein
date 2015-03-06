/*
** get_next_line.h for get next line in /home/gaspar_q/rendu/CPE_2014_get_next_line/include
** 
** Made by quentin gasparotto
** Login   <gaspar_q@epitech.net>
** 
** Started on  Mon Nov 17 15:16:33 2014 quentin gasparotto
** Last update Thu Dec 11 13:29:52 2014 quentin gasparotto
*/

#ifndef GET_NXT_LINE_H_
# define GET_NXT_LINE_H_

# define	LINE_LEN 4096

char	*my_realloc_str(char *, int);
char	*read_line(const int fd, char *read_line, int size);
char	*get_next_line(const int fd);

#endif /* !GET_NXT_LINE_H_  */
