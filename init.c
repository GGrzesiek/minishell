
#include "minishell.h"

static t_env	*new_env_node(char *str)
{
	t_env	*node;
  char *sub;
	int	i;

	node = (t_env *) malloc(sizeof(t_env));
	if(!node)
		return(NULL);
	i=0;
	while(str[i] && str[i] != '=')
		i++;
  sub = ft_substr(str,0,i);
	if(sub != NULL)
		node->key = sub;
	if(str[i] == '=')
		node->value = ft_strdup(str + i + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return(node);
}

static void	env_add_back(t_env **head, t_env *new_node)
{
	t_env *curr;

	if(!head || !new_node)
		return;
	if (!*head)
	{
		*head = new_node;
		return;
	}
	curr = *head;
	while(curr->next)
		curr = curr->next;
	curr->next = new_node;
}

static void init_path(t_shell *shell)
{
  int i;
  char **paths;
  char *raw;
  char *tmp;

  raw = getenv("PATH");
  if (!raw)
    end(shell, "path not found\n");
  paths = ft_split(raw, ':');
  if (!paths)
    end(shell, "paths malloc error\n");
  i = 0;
  while(paths[i])
  {
    tmp = paths[i];
    paths[i] = ft_strjoin(paths[i], "/");
    free(tmp);
    i++;
  }
  shell->paths = paths;
}

void init_env_list(t_shell *shell, char **envp)
{
	int	i;
  t_env *new_node;

	shell->env_list = NULL;
	if(!envp || !*envp)
		return ;

	i = 0;
	while(envp[i])
	{
    new_node = new_env_node(envp[i]);
    if (!new_node)
      end(shell, "envp new node malloc error\n");
		env_add_back(&shell->env_list, new_node);
		i++;
	}
}

void init_shell(t_shell *shell, char **envp)
{
  shell->envp = envp;
	shell->exit_code = 0;
	shell->cmds = NULL;
  shell->paths = NULL;
  
  init_path(shell);
	init_env_list(shell, envp);
  if (!shell->paths)
    end(shell, "paths not initialized\n");
}