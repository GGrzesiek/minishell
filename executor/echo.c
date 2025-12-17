/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:40:04 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:40:05 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static void	printarr(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return ;
	while (args[i + 1])
	{
		printf("%s ", *args);
		args++;
	}
	printf("%s", *args);
}

static int	run_child(t_shell *shell, t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			end(shell, "dup2 input fail");
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			end(shell, "dup2 output fail");
		close(cmd->fdout);
	}
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
		return (printarr(&cmd->args[2]), 0);
	else
		return (printarr(&cmd->args[1]), printf("\n"), 0);
}

int	recho(t_shell *shell, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
	{
		run_child(shell, cmd);
		end(shell, NULL);
	}
	else
	{
		if (cmd->fdout != STDOUT_FILENO)
			close(cmd->fdout);
	}
	return (0);
}

int	process_end(t_shell *shell, t_cmd *cmd)
{
	char	*exit_code;
  

	exit_code = cmd->args[1];
	if (exit_code)
	{
    if (cmd->args[2])
      return (shperror(cmd->args[0], " too many arguments"), 1);
		if (ft_isnumber(exit_code))
		{
			shell->exit_code = ft_atoi(exit_code);
		} else
      return (shperror(cmd->args[0], " numeric argument required"), 1);
	}
	end(shell, NULL);
	return (0);
}
