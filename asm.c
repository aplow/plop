#include "asmx.h"

char	*get_arg_types(t_kitten *kitten);

int	get_mnemonique(t_kitten *kitten)
{
  int	i;

  i = 0;
  while (op_tab[i].mnemonique &&
	 (strncmp(&kitten->line[kitten->i],
		 op_tab[i].mnemonique,
		 strlen(op_tab[i].mnemonique)) ||
	  kitten->line[kitten->i + strlen(op_tab[i].mnemonique)] != ' '))
    i++;
  if (op_tab[i].mnemonique == 0)
    return (0);
  kitten->i += strlen(op_tab[i].mnemonique) + 1;
  return (i + 1);
}

void	print_error(int	id, t_kitten *kitten)
{
  char	*err_msg[5] = {
    "err 1 line %d\n",
    "err 2 line %d\n",
    "err 3 line %d\n",
    "err 4 line %d\n",
    "err 5 line %d\n"
  };

  printf(err_msg[id - 1], kitten->line_nbr);
  printf("%s\n", kitten->line);
  printf("%*c\n", kitten->i, '^');
  free(kitten->line);
  free(kitten->hex);
  exit(0);
}

void	get_label(t_kitten *kitten)
{
  while (is_label_char(kitten->line[kitten->i]))
    kitten->i++;
  if (kitten->line[kitten->i] != LABEL_CHAR)
    kitten->i = 0;
  else
    kitten->i += 2;
}

int	convert_line(t_kitten *kitten)
{
  unsigned char	tmp;
  unsigned char	*label;
  int   i;

  //printf("convert line %d: %s\n", kitten->line_nbr, kitten->line);
  get_label(kitten);
  if (kitten->line[kitten->i] && (tmp = get_mnemonique(kitten)) != 0)
    kitten->hex[kitten->offset++] = tmp;
  if (kitten->line[kitten->i] && tmp == 0)
    print_error(2, kitten);
  label = get_arg_types(kitten);
  i = 0;
  int   j;
  while (label[i])
    {
      //j = 7;
      printf("%#.2x,", kitten->hex[kitten->offset] = label[i++]);
      //while (j >= 0)
      //printf("%d", (kitten->hex[kitten->offset] & (1 << j--)) ? 1 : 0);
      kitten->offset++;
      //printf("\n");
    }
  free(label);
  while (kitten->line[kitten->i])
    {
      j = 0;
      label = get_arg_value(kitten);
      while (j < kitten->arg_size)
	printf("%#.2x,", label[j++]);
      printf("\n");
    }
  return (0);
}

void	*xmalloc(int size)
{
  char	*ptr;
  
  if ((ptr = malloc(size)) == NULL)
    {
      printf("malloc error\n");
      exit(1);
    }
  while (size > 0)
    ptr[size-- - 1] = 0;
  return ((void *)ptr);
}

int	main(int argc, char **argv)
{
  int		fd;
  t_kitten	kitten;

  if (argc != 2)
    return (1);
  fd = open(argv[1], O_RDONLY);
  kitten.line_nbr = 0;  
  kitten.hex = xmalloc(512);
  kitten.offset = 0;
  while (kitten.line = get_next_line(fd))
    {
      kitten.line_nbr++;
      kitten.i = 0;
      convert_line(&kitten);
      free(kitten.line);
    }
  close(fd);
  int	i = 0;
  while (i < kitten.offset)
    printf("%#.2x,", kitten.hex[i++]);
  printf("\n");
  free(kitten.hex);
  return (0);
}
