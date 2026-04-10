#include "minishell.h"

void end(t_shell *shell, char *msg)
{
  t_env *lst;
  t_env *tmp;

  // FREE ENV LIST
  rl_clear_history();
  lst = shell->env_list;
  while (lst)
  {
    tmp = lst;
    lst = lst->next;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
  }
  free_split(shell->paths);
  if (msg)
    write(STDERR_FILENO, msg, ft_strlen(msg));
  exit(shell->exit_code);
}

void	free_split(char **sp)
{
	int	i;

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