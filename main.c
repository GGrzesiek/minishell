
#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
  static t_data data;

  (void) data;
  (void) argc;
  (void) argv;
  (void) envp;
  while(1)
  {
    if (errno)
      return(perror(strerror(errno)), 1);
  }
}