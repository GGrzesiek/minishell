
#include "minishell.h"

static t_env	*new_env_node(char *str)
{
	t_env	*node;
	int	i;

	node = malloc(sizeof(t_env));
	if(!node)
		return(NULL);
	i=0;
	while(str[i] && str[i] != '=')
		i++;
	if(ft_substr(str,0,i) != NULL)
		node->key = ft_substr(str,0,i);
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
void init_env_list(t_shell *shell,char **envp)
{
	int	i;

	shell->env_list = NULL;
	if(!envp || !*envp)
		return ;

	i = 0;
	while(envp[i])
	{
		env_add_back(&shell->env_list, new_env_node(envp[i]));
		i++;
	}
}

void init_shell(t_shell *shell, char **envp)
{
	shell->exit_code = 0;
	shell->cmds = NULL;
	init_env_list(shell, envp);
}