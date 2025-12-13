#include "./../minishell.h"


// if fd already exists from a pipe, close it and override
void open_redir(t_shell *shell, t_cmd *cmd)
{
  (void) shell;
  t_redir *redir;

  redir = cmd->redirs;
  while (redir)
  {
    if (redir->type == TOKEN_REDIR_IN)
      {}
    if (redir->type == TOKEN_REDIR_OUT)
      {}
    if (redir->type == TOKEN_REDIR_APPEND)
      {}
    if (redir->type == TOKEN_REDIR_HEREDOC)
      {}
  }
}

void execute_chain(t_shell *shell, t_cmd *cmd)
{
  while (cmd)
  {
    if (cmd->next)
    {
      // open pipe
    }
    open_redir(shell, cmd);
    execute_command(shell, cmd);
    cmd=cmd->next;
  }
}

void	execute_command(t_shell *shell, t_cmd *cmd)
{
	char *name;

	name = cmd->args[0];
	if (ft_strncmp("exit", name, 5) == 0)
		end(shell, NULL);
	else if (ft_strncmp("cd", name, 3) == 0)
		change_directory(shell, cmd);
	else if (ft_strncmp("export", name, 7) == 0)
		export(shell, cmd);
	else if (ft_strncmp("unset", name, 6) == 0)
		unset(shell, cmd);
	else if (ft_strncmp("env", name, 4) == 0)
		print_env(shell, &shell->env_list);
	else
		process_native_command(shell, cmd);
}