/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:52:53 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:52:54 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exec(t_shell *shell, t_cmd *cmd, t_pipe_ctx *ctx)
{
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (ctx->idx > 0)
		dup2(ctx->pipes[ctx->idx - 1][0], STDIN_FILENO);
	if (ctx->idx < ctx->n - 1)
		dup2(ctx->pipes[ctx->idx][1], STDOUT_FILENO);
	close_pipes(ctx->pipes, ctx->n - 1);
	if (apply_redirections(shell, cmd) < 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		dispatch_builtin(shell, cmd);
		exit(shell->exit_code);
	}
	exec_external(shell, cmd);
}

static void	spawn_children(t_shell *shell, t_cmd *cmds, t_pipe_ctx *ctx,
		pid_t *pids)
{
	t_cmd	*cmd;

	cmd = cmds;
	ctx->idx = 0;
	while (cmd)
	{
		pids[ctx->idx] = fork();
		if (pids[ctx->idx] < 0)
			end(shell, "fork error\n");
		if (pids[ctx->idx] == 0)
			child_exec(shell, cmd, ctx);
		cmd = cmd->next;
		ctx->idx++;
	}
}

static int	wait_children(pid_t *pids, int n)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < n)
		waitpid(pids[i++], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

void	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	t_pipe_ctx	ctx;
	pid_t		*pids;
	t_cmd		*cmd;

	ctx.n = 0;
	cmd = cmds;
	while (cmd)
	{
		ctx.n++;
		cmd = cmd->next;
	}
	setup_heredocs(shell, cmds);
	ctx.pipes = init_pipes(shell, ctx.n);
	pids = malloc(sizeof(pid_t) * ctx.n);
	if (!pids)
		end(shell, "malloc error\n");
	spawn_children(shell, cmds, &ctx, pids);
	cleanup_pipeline(cmds, ctx.pipes, ctx.n - 1);
	shell->exit_code = wait_children(pids, ctx.n);
	free(ctx.pipes);
	free(pids);
}
