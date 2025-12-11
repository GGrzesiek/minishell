
#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
  t_shell shell;
  char *line;

  shell.argc = argc;
	shell.argv = argv;

  init_shell(&shell, envp);
  setup_signals();

  while (1)
  {
    line = readline("mini(s)hell> ");

    if(!line)
      end(&shell, "readline error\n");

    if(*line)
    {
      add_history(line);

      t_cmd *cmd = init_single_cmd(&shell, line);
      execute_command(&shell, cmd, STDIN_FILENO, STDOUT_FILENO);
      free_split(cmd->args);
      free(cmd);
    }
  }
}