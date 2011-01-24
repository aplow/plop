/*
** is_label_char.c for corewar in /home/corbre_k//projets/corewar/assembleur
** 
** Made by killian corbrejaud
** Login   <corbre_k@epitech.net>
** 
** Started on  Sat Jan 22 17:57:58 2011 killian corbrejaud
** Last update Sat Jan 22 21:43:15 2011 gregoire clermont
*/

#include "op.h"

int	is_label_char(char c)
{
  char *chars;
  int	i;

  chars = LABEL_CHARS;
  i = 0;
  while (chars[i] != '\0')
    if (chars[i++] == c)
      return (1);
  return (0);
}
