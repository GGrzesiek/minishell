#include "./../minishell.h"

void open_pipe(t_cmd *cmd)
{
  int p[2];

  if (pipe(p) == -1)
    end(data, "pipe fail");
  cmd->fdout = p[0];
  cmd->next->fdin = p[1];
}

// overrides pipe
int open_redir(t_cmd *cmd)
{
  t_redir *redir;
  int fd;

  redir = cmd->redirs;
  while (redir)
  {
    if (redir->type == TOKEN_REDIR_IN)
    {
      fd = open(redir->file, O_RDONLY);
      if (fd == -1)
        return(perror("File not found"), 1)
      if (cmd->fdin != STDIN_FILENO)
        close(cmd->fdin);
      cmd->fdin = fd;
    }
    if (redir->type == TOKEN_REDIR_HEREDOC)
    {
      // TODO
    }
    if (redir->type == TOKEN_REDIR_OUT)
    {
      fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC);
      if (fd == -1)
        return(perror("Error creating truncate file"), 1)
      if (cmd->fdout != STDOUT_FILENO)
        close(cmd->fdout);
      cmd->fdout = fd;
    }
    if (redir->type == TOKEN_REDIR_APPEND)
    {
      fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND);
      if (fd == -1)
        return(perror("Error oppening append file"), 1)
      if (cmd->fdout != STDOUT_FILENO)
        close(cmd->fdout);
      cmd->fdout = fd;
    }
  }
  return (0);
}

int	execute_command(t_shell *shell, t_cmd *cmd)
{
	char *name;

	name = cmd->args[0];
	if (ft_strncmp("exit", name, 5) == 0)
		end(shell, NULL);
	else if (ft_strncmp("cd", name, 3) == 0)
		return(change_directory(shell, cmd));
	else if (ft_strncmp("export", name, 7) == 0)
		return(export(shell, cmd));
	else if (ft_strncmp("unset", name, 6) == 0)
		return(unset(shell, cmd));
	else if (ft_strncmp("env", name, 4) == 0)
		return(print_env(shell, &shell->env_list));
	else
		return(process_native_command(shell, cmd));
}

void close_pipe(t_cmd *cmd)
{
  if (cmd->fdin != STDIN_FILENO)
    close(cmd->fdin);
  if (cmd->fdout != STDOUT_FILENO)
    close(cmd->fdout);
  if (cmd->next && cmd->next->fdin != STDIN_FILENO)
    close(cmd->next->fdin);
}

int execute_chain(t_shell *shell, t_cmd *cmd)
{
  cmd->fdin = STDIN_FILENO;
  while (cmd)
  {
    cmd->fdout = STDOUT_FILENO;
    if (cmd->next)
      open_pipe(cmd);
    if (open_redir(cmd))
      return (close_pipe(cmd), 1);
    if (execute_command(shell, cmd));
      return (close_pipe(cmd), 1);
    cmd=cmd->next;
  }
  return(0);
}