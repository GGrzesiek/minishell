
#include "minishell.h"

void	init_path(t_shell *shell)
{
	int		i;
	char	**paths;
	char	*raw;
	char	*tmp;

	raw = env_get(&shell->env_list, "PATH");
	if (!raw)
  {
    shell->paths=NULL;
		return ;
  }
	paths = ft_split(raw, ':');
	if (!paths)
		end(shell, "paths malloc error\n");
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	shell->paths = paths;
}

void	init_env_list(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_node;

	shell->env_list = NULL;
	if (!envp || !*envp)
		return ;
	i = 0;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
			end(shell, "envp new node malloc error\n");
		env_add_back(&shell->env_list, new_node);
		i++;
	}
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->exit_code = 0;
	shell->cmds = NULL;
	shell->paths = NULL;

	init_env_list(shell, envp);
	init_path(shell);
}