/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:12:45 by emilka            #+#    #+#             */
/*   Updated: 2026/04/13 12:12:46 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static char	*validate_with_env(t_shell *shell, t_cmd *cmd, char *env_var)
{
	char	*path;
	char	*part;
	char	*base_dir;

	base_dir = env_get(&shell->env_list, env_var);
	part = ft_substr(cmd->args[0], 1, ft_strlen(cmd->args[0]));
	path = ft_strjoin(base_dir, part);
	free(part);
	if (!path || access(path, F_OK) == -1)
	{
		if (path)
			free(path);
		return (NULL);
	}
	return (path);
}

static char	*validate_in_paths(t_shell *shell, char *name)
{
	char	*path;
	int		j;

	if (name[0] == '/')
	{
		if (access(name, F_OK) == -1)
			return (NULL);
		path = ft_strdup(name);
		if (!path)
			end(shell, "malloc error\n");
		return (path);
	}
	j = -1;
	while (shell->paths && shell->paths[++j])
	{
		path = ft_strjoin(shell->paths[j], name);
		if (!path)
			end(shell, "malloc error\n");
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	if (!shell->paths && access(name, F_OK) == 0)
		return (ft_strdup(name));
	return (NULL);
}

static int	handle_not_found(t_shell *shell, char *name)
{
	if (name[0] == '.' || name[0] == '/' || name[0] == '~')
		shperror(name, "No such file or directory");
	else
		shperror(name, "command not found");
	shell->exit_code = 127;
	return (1);
}

static int	validate_access(t_shell *shell, t_cmd *cmd, char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		free(cmd->path);
		shperror(cmd->args[0], "Is a directory");
		shell->exit_code = 126;
		return (1);
	}
	if (access(cmd->path, X_OK) == -1)
	{
		free(cmd->path);
		shperror(cmd->args[0], "Permission denied");
		shell->exit_code = 126;
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
	else
		path = validate_in_paths(shell, name);
	cmd->path = path;
	if (!path)
		return (handle_not_found(shell, name));
	return (validate_access(shell, cmd, path));
}
