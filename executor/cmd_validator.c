/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:37:01 by emilka            #+#    #+#             */
/*   Updated: 2026/03/11 13:37:12 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static char	*validate_as_is(t_shell *shell, char *name)
{
	char	*path;

	path = NULL;
	if (access(name, F_OK) == 0)
	{
		path = ft_strdup(name);
		if (!path)
			end(shell, "command path malloc error\n");
	}
	return (path);
}

static char	*validate_with_env(t_shell *shell, t_cmd *cmd, char *env_var)
{
	char	*path;
	char	*part;
	char	*base_dir;

	base_dir = env_get(&shell->env_list, env_var);
	part = ft_substr(cmd->args[0], 1, ft_strlen(cmd->args[0]));
	path = ft_strjoin(base_dir, part);
	free(part);
	return (path);
}

static char	*validate_in_paths(t_shell *shell, char *name)
{
	char	*path;
	char	**paths;
	int		j;

	j = 0;
	path = NULL;
	paths = shell->paths;
	if (paths)
	{
		while (paths[j])
		{
			path = ft_strjoin(paths[j], name);
			if (!path)
				end(shell, "command full path malloc error\n");
			if (access(path, F_OK) == 0)
				break ;
			free(path);
			path = NULL;
			j++;
		}
	}
	else
		path = validate_as_is(shell, name);
	return (path);
}

int	validate_access(t_cmd *cmd, char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		free(cmd->path);
		shperror(cmd->args[0], "Is a directory");
		return (1);
	}
	if (access(cmd->path, X_OK) == -1)
	{
		free(cmd->path);
		shperror(cmd->args[0], "Permission denied");
		return (1);
	}
	return (0);
}

int	validate_command(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp("./", name, 2) == 0)
		path = validate_with_env(shell, cmd, "PWD");
	else if (ft_strncmp("~/", name, 2) == 0)
		path = validate_with_env(shell, cmd, "HOME");
	else if (ft_strncmp("/", name, 1) == 0)
		path = validate_as_is(shell, name);
	else
		path = validate_in_paths(shell, name);
	cmd->path = path;
	if (!path)
	{
		shperror(cmd->args[0], "command not found");
		shell->exit_code = 127;
		return (1);
	}
	if (validate_access(cmd, path))
	{
		shell->exit_code = 126;
		return (1);
	}
	return (0);
}
