#include "./../minishell.h"

void open_pipe(t_shell *shell, t_cmd *cmd)
{
  int p[2];

  if (pipe(p) == -1)
    end(shell, "pipe fail");
  cmd->fdout = p[1]; // write end
  cmd->next->fdin = p[0]; // read end
}

int open_redir(t_cmd *cmd)
{
  t_redir *redir;
  int fd;

  redir = cmd->redirs;
  while (redir)
  {
    if (redir->type == TOKEN_REDIR_IN)
    {
      if (cmd->fdin != STDIN_FILENO)
        close(cmd->fdin);
      fd = open(redir->file, O_RDONLY);
      if (fd == -1)
        return(perror(""), 1);
      cmd->fdin = fd;
    }
    else if (redir->type == TOKEN_REDIR_HEREDOC)
    {
      // TODO
    }
    else if (redir->type == TOKEN_REDIR_OUT)
    {
      if (cmd->fdout != STDOUT_FILENO)
        close(cmd->fdout);
      fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC);
      if (fd == -1)
        return(perror(""), 1);
      cmd->fdout = fd;
    }
    else if (redir->type == TOKEN_REDIR_APPEND)
    {
      if (cmd->fdout != STDOUT_FILENO)
        close(cmd->fdout);
      fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND);
      if (fd == -1)
        return(perror(""), 1);
      cmd->fdout = fd;
    }
    redir=redir->next;
  }
  return (0);
}

int	execute_command(t_shell *shell, t_cmd *cmd)
{
	char *name;

  free_split(shell->paths);
  init_path(shell);
	name = cmd->args[0];
  if (!name)
    return(close_pipe(cmd), 1);
	if (ft_strncmp("exit", name, 5) == 0)
		end(shell, NULL);
	else if (ft_strncmp("cd", name, 3) == 0)
		return(change_directory(shell, cmd));
	else if (ft_strncmp("export", name, 7) == 0)
		return(export(shell, cmd));
	else if (ft_strncmp("unset", name, 6) == 0)
		return(unset(shell, cmd));
	else if (ft_strncmp("env", name, 4) == 0)
		return(print_env(shell, cmd));
	else
		return(process_native_command(shell, cmd));
  return (0);
}

int execute_cmd_chain(t_shell *shell, t_cmd *cmd)
{
  cmd->fdin = STDIN_FILENO;
  while (1)
  {
    cmd->fdout = STDOUT_FILENO;
    if (cmd->next)
      open_pipe(shell, cmd);
    if (open_redir(cmd))
      return (close_pipe(cmd), 1);
    if (execute_command(shell, cmd))
      return (close_pipe(cmd), 1);
    if (!cmd->next)
      break ;
    cmd=cmd->next;
  }
  if (cmd->fdout != STDOUT_FILENO)
    close(cmd->fdout);
  return(0);
}