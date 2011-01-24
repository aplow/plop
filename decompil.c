#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
  int	fd;
  char buff[1];

  fd = open(argv[1], O_RDONLY);
  while (read(fd, buff, 1))
      printf("%#.2x,", buff[0]);
  printf("\n");
  return (0);
}
