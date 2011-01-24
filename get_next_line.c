/*
** get_next_line.c for get_next_line in /home/corbre_k//projets/get_next_line
** 
** Made by killian corbrejaud
** Login   <corbre_k@epitech.net>
** 
** Started on  Thu Nov 11 13:40:12 2010 killian corbrejaud
** Last update Sat Jan 22 21:43:33 2011 gregoire clermont
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	get_char(const int fd, char *c)
{
  static int	i = 0;
  static char	buff[READ_SIZE];
  static int	nb_r = READ_SIZE;

  if (i >= nb_r || i == 0)
    {
      i = 0;
      if ((nb_r = read(fd, buff, READ_SIZE)) < 0)
	exit(0);
    }
  if (nb_r == 0)
    {
      *c = '\0';
      i = -1;
    }
  else
    if (buff[i] == '\n')
      *c = '\0';
    else
      *c = buff[i];
  i++;
  return (nb_r);
}

char	*get_next_line(const int fd)
{
  char	*next_line;
  int	i;
  int	nb_r;

  i = 0;
  nb_r = 1;
  next_line = malloc((READ_SIZE + 1) * sizeof(*next_line));
  nb_r = get_char(fd, &next_line[i]);
  if (nb_r == 0)
    return (NULL);
  while (next_line[i] != '\0')
    {
      if (i % READ_SIZE == 0)
	next_line = realloc(next_line, i + READ_SIZE + 1);
      nb_r = get_char(fd, &next_line[++i]);
    }
  next_line[++i] = '\0';
  return (next_line);
}
