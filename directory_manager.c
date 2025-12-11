#include "minishell.h"

/* bufered wrapper for getcwd*/
char *getcwdir(t_shell *shell)
{
  static char buffer[PATH_MAX] = "";
  getcwd(buffer, sizeof(buffer));
  if (!*buffer)
    end(shell, "error getting cwd\n");
  return(buffer);
}

void change_directory(t_shell *shell, char *to)
{
  if (!to)
    to = "/~";
  (void) shell;
}