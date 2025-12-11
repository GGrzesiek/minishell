#include "minishell.h"

void write_all(t_shell *shell, int fd, char *content)
{
  if (fd < 0)
    end(shell, "invalid fd\n");
  if (content)
    write(fd, content, ft_strlen(content));
  close(fd);
}

/* TODO make sure it works with relative paths and directory changes, same for write */
// char *open_all(t_shell *shell, char *path)
// {
//   int fd;
  
//   fd = open(path, "O_RDONLY");
//   return (read_all(shell, fd));
// }

char *read_all(t_shell *shell, int fd)
{
  int bread;
  char buffer[101];
  char *content;
  char *tmp;

  if (fd < 0)
    end(shell, "invalid fd\n");
  bread = 1;
  content = NULL;
  while(bread > 0)
  {
    bread = read(fd, buffer, 100);
    buffer[bread] = '\0';
    tmp = content;
    content = ft_strjoin(content, buffer);
    if(!content)
        end(shell, "file read_all malloc error\n");
    free(tmp);
  }
  close(fd);
  return (content);
}