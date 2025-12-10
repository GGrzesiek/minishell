
#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
  t_shell shell;
  char *line;

  (void)argc;
  (void)argv;

  init_shell(&shell, envp);
  setup_signals();

  while (1)
  {
    line = readline("mini(s)hell> ");

    if(!line)
    {
      printf("exit\n");
      break;
    }

    if(*line)
      add_history(line);
    
    if(ft_strncmp(line, "exit",5) == 0)
    {
      free(line);
      break;
    }
  }
  
  cleanup_shell(&shell);
  return(shell.exit_code);
}