/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:52:41 by cscache           #+#    #+#             */
/*   Updated: 2025/06/26 11:09:50 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		if (p->pipes[i][0] >= 0)
			close(p->pipes[i][0]);
		if (p->pipes[i][1] >= 0)
			close(p->pipes[i][1]);
		i++;
	}
	if (p->fd_infile >= 0)
		close(p->fd_infile);
	if (p->fd_outfile >= 0)
		close(p->fd_outfile);
}

void	create_dup(t_pipex *p, int i)
{
	if (i == 0)
	{
		dup2(p->fd_infile, 0);
		dup2(p->pipes[i][1], 1);
	}
	else if (i == p->nb_cmds - 1)
	{
		dup2(p->pipes[i - 1][0], 0);
		dup2(p->fd_outfile, 1);
	}
	else
	{
		dup2(p->pipes[i - 1][0], 0);
		dup2(p->pipes[i][1], 1);
	}
	close_pipes(p);
}

void	execute_child(t_pipex *p, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("[Pipex] Error: fork");
		free_struct(p);
		exit_code(1);
	}
	if (pid == 0)
	{
		create_dup(p, i);
		if (i == 0 && p->fd_infile < 0)
		{
			perror("[Pipex] Error: infile");
			return (free_struct(p), exit_code(1));
		}
		if (i == p->nb_cmds - 1 && p->fd_outfile < 0)
		{
			perror("[Pipex] Error: outfile");
			return (free_struct(p), exit_code(1));
		}
		execute_cmd(p, i);
	}
	p->pids[i] = pid;
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

int	pipe_and_fork(t_pipex *p)
{
	int		i;
	int		status;
	pid_t	current_pid;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (i < p->nb_cmds)
	{
		execute_child(p, i);
		i++;
	}
	close_pipes(p);
	i = 0;
	while (i < p->nb_cmds)
	{
		current_pid = waitpid(p->pids[i], &status, 0);
		if (current_pid == p->pids[p->nb_cmds - 1])
			exit_code = get_exit_code(status);
		i++;
	}
	free_struct(p);
	return (exit_code);
}
