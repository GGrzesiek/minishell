#include "./../minishell.h"

void execute_chain(t_shell *shell, t_cmd *cmd)
{
  t_redir *curr;

  curr = cmd->redirs;
  while(curr)
  {
    if (curr->type == TOKEN_REDIR_IN)
      ;
    if (curr->type == TOKEN_REDIR_OUT)
      ;
    if (curr->type == TOKEN_REDIR_APPEND)
      ;
    if (curr->type == TOKEN_REDIR_HEREDOC)
      ;
  }
  if (cmd->prev)
    ;
  if (cmd->next)
    ;
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