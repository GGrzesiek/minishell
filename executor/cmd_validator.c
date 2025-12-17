/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:39:11 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:39:34 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static char	*validate_as_is(t_shell *shell, char *name)
{
	char	*path;

	path = NULL;
	if (access(name, X_OK) == 0)
	{
		path = ft_strdup(name);
		if (!path)
			end(shell, "command path malloc error\n");
	}
	return (path);
}

static char	*validate_as_rel(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*part;
	char	*cwd_dir;

	cwd_dir = env_get(&shell->env_list, "PWD");
	part = ft_substr(cmd->args[0], 1, ft_strlen(cmd->args[0]));
	path = ft_strjoin(cwd_dir, part);
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
			if (access(path, X_OK) == 0)
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

static char	*validate_as_user(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*part;
	char	*user_dir;

	user_dir = env_get(&shell->env_list, "HOME");
	part = ft_substr(cmd->args[0], 1, ft_strlen(cmd->args[0]));
	path = ft_strjoin(user_dir, part);
	free(part);
	return (path);
}

int validate_access(t_cmd *cmd, char *path)
{
  struct stat path_stat;

  stat(path, &path_stat);
  if (S_ISDIR(path_stat.st_mode))
    return (free(cmd->path), shperror(cmd->args[0], " Is a directory"), 1);
  if (access(cmd->path, X_OK) == -1)
    return (free(cmd->path), shperror(cmd->args[0], " Permission denied"), 1);
  return (0);
}

int	validate_command(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*name;

	path = NULL;
	name = cmd->args[0];
	if (ft_strncmp("./", name, 2) == 0)
	{
		path = validate_as_rel(shell, cmd);
	}
	else if (ft_strncmp("~/", name, 2) == 0)
	{
		path = validate_as_user(shell, cmd);
	}
	else if (ft_strncmp("/", name, 1) == 0)
	{
		path = validate_as_is(shell, name);
	}
	else
	{
		path = validate_in_paths(shell, name);
	}
	cmd->path = path;
  return (validate_access(cmd, path));
}
