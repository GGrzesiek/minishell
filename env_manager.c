#include "minishell.h"

t_env	*new_env_node(char *str)
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

void	env_add_back(t_env **head, t_env *new_node)
{
	t_env *curr;
  size_t len;

	if(!head || !new_node)
		return;
  if(!new_node->key || !new_node->value)
  {
    free(new_node->value);
    free(new_node->key);
    free(new_node);
    return ;
  }
  len = ft_strlen(new_node->key);
	if (!*head)
  {
    *head = new_node;
    return ;
  }
	curr = *head;
	while(curr->next)
  {
    if (ft_strncmp(curr->key, new_node->key, len) == 0)
    {
      free(new_node->key);
      free(new_node->value);
      free(new_node);
      return;
    }
    curr = curr->next; 
  }
  if (ft_strncmp(curr->key, new_node->key, len) == 0)
  {
    free(new_node->key);
    free(new_node->value);
    free(new_node);
    return;
  }
	curr->next = new_node;
}

void	env_del(t_env **head, char *key)
{
  size_t len;
  t_env *curr;
  t_env *prev;
  t_env *tmp;

  if(!head || !key || !*key)
		return;
	if (!*head)
    return;
  curr = *head;
  prev = NULL;
  len = ft_strlen(key);
  while(curr)
  {
    if (ft_strncmp(curr->key, key, len) == 0)
    {
      tmp = curr;
      if (!prev)
        *head = curr->next;
      else
        prev->next = curr->next;
      free(tmp->value);
      free(tmp->key);
      free(tmp);
      return;
    }
    prev = curr;
    curr = curr->next; 
  }
}


char *env_get(t_env **head, char *key)
{
  size_t len;
  t_env *curr;

  if(!head || !key || !*key)
		return (NULL);
	if (!*head)
    return (NULL);
  curr = *head;
  len = ft_strlen(key);
  while(curr)
  {
    if (ft_strncmp(curr->key, key, len) == 0)      
      return (curr->value);
    curr = curr->next; 
  }
  return(NULL);
}

void print_env(t_env **head)
{
  int pid;
  t_env *curr;

  pid = fork()
  if (pid < 0)
    end(shell, "fork failed\n");
  else if (pid == 0)
  {
    if (output_fd != STDOUT_FILENO)
    {
      if (dup2(output_fd, STDOUT_FILENO) == -1)
        end(shell, "dup2 output fail");
      close(output_fd);
    }
    curr = *head;
    while(curr)
    {
      printf("%s=%s\n", curr->key, curr->value);
      curr = curr->next; 
    }
  }
  else 
    wait(0);
}