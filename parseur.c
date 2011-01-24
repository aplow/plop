/*
** parseur.c for corwar in /home/corbre_k//projets/corewar/assembleur
** 
** Made by killian corbrejaud
** Login   <corbre_k@epitech.net>
** 
** Started on  Sat Jan 22 18:08:30 2011 killian corbrejaud
** Last update Sat Jan 22 22:49:43 2011 gregoire clermont
*/

#include "asmx.h"

unsigned char	*get_arg_types(t_kitten *kitten)
{
  int	i;
  int	j;
  char	bool;
  unsigned char	*hex_param;

  bool = 0;
  j = 0;
  hex_param = xmalloc(1);
  i = kitten->i;
  while (kitten->line[i] != '\0')
    {
      if (j % 4 == 0)
	{
	  hex_param = realloc(hex_param, j / 4 + 1);
	  hex_param[j / 4] = 0;
	}
      if (kitten->line[i] == SEPARATOR_CHAR && bool == 1)
	bool = 0;
      else if (kitten->line[i] == SEPARATOR_CHAR)
	hex_param[j / 4] |= 3 << 6 - 2 * (j++ % 4);
      if (kitten->line[i] == DIRECT_CHAR)
	{
	  hex_param[j / 4] |= 2 << 6 - 2 * (j++ % 4);
	  bool = 1;
	}
      if (kitten->line[i] == 'r')
	{
	  hex_param[j / 4] |= 1 << 6 - 2 * (j++ % 4);
	  bool = 1;
	}
      i++;
    }
  if (bool == 0 && i != kitten->i)
    hex_param[j / 4] |= 3 << 6 - 2 * (j++ % 4);
  hex_param[j / 4 + 1] = '\0';
  return(hex_param);
}

unsigned char	*get_arg_value(t_kitten *kitten)
{
  unsigned char	*value;
  int	result;
  int	i;

  if (kitten->line[kitten->i] == 'r')
    {
      value = xmalloc(1);
      i = 0;
      value[1] = '\0';
      kitten->arg_size = 1;
      kitten->i++;
    }
  else if (kitten->line[kitten->i] == '%')
    {
      value = xmalloc(DIR_SIZE + 1);
      i = DIR_SIZE - 1;
      value[DIR_SIZE] = '\0';
      kitten->arg_size = DIR_SIZE;
      kitten->i++;
    }
  else
    {
      value = xmalloc(IND_SIZE);
      i = IND_SIZE - 1;
      value[IND_SIZE] = '\0';
      kitten->arg_size = IND_SIZE;
    }
  result = 0;
  while (kitten->line[kitten->i] && kitten->line[kitten->i] != ',')
    {
      //printf("%c\n", kitten->line[kitten->i]);
      result = 10 * result + kitten->line[kitten->i++] - '0';
    }
  //printf("=%d\n", result);
  while (i >= 0)
    {
      //printf("value[%d] = %d\n", i, result % 255);
      value[i--] = result % 255;
      result /= 255;
    }
  kitten->i++;
  return (value);
}
