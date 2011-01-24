#ifndef ASMX_H
#define ASMX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "op.h"
#include "get_next_line.h"

int	is_label_char(char c);

typedef struct	s_kitten
{
  char	*line;
  unsigned char	*hex;
  int	offset;
  int	line_nbr;
  int	i;
  int	arg_size;
}		t_kitten;

void	*xmalloc(int size);

#endif
