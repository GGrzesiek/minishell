#include "minishell.h"

void	free_env(t_env *node)
{
	free(node->value);
	free(node->key);
	free(node);
}

void free_env_lst(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_env(tmp);
	}
}

void free_cmd_chain(t_cmd *cmd)
{
  t_cmd	*tmp;
  t_redir *redir;
  t_redir *rtmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
    redir = tmp->redirs;
    free_split(tmp->args);
    free(tmp);
    while(redir)
    {
      rtmp = redir;
      redir = redir->next;
      free(rtmp);
    }
	}
}

void	end(t_shell *shell, char *msg)
{
	rl_clear_history();
  free_cmd_chain(shell->cmds);
  free_env_lst(shell->env_list);
	free_split(shell->paths);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(shell->exit_code);
}

void	free_split(char **sp)
{
	int i;

	i = 0;
	if (sp)
	{
		while (sp[i])
		{
			free(sp[i]);
			i++;
		}
		free(sp);
	}
}

void free_tokens(t_token *head)
{
  t_token *tmp;

  while(head)
  {
    tmp = head;
    head = head->next;
    free(tmp->value);
    free(tmp);
  }
}
void free_redirs(t_redir *head)
{
    t_redir *tmp;

    while(head)
    {
      tmp= head;
      head = head->next;
      if(tmp->file)
        free(tmp->file);
      free(tmp);
    }
}
void free_cmds(t_cmd *head)
{
  t_cmd *tmp;

  while(head)
  {
    tmp = head;
    head = head->next;
    if(tmp->args)
      free_split(tmp->args);
    if(tmp->path)
      free(tmp->path);
    if(tmp->redirs)
      free_redirs(tmp->redirs);
	free(tmp);
  }
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