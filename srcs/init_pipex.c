/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:55:35 by cscache           #+#    #+#             */
/*   Updated: 2025/06/26 10:28:17 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipes(t_pipex *p)
{
	int	i;

	p->pipes = malloc(sizeof(int *) * (p->nb_cmds - 1));
	if (!p->pipes)
	{
		perror("[Pipex] Error: malloc pipes");
		exit_code(1);
	}
	i = 0;
	while (i < p->nb_cmds - 1)
	{
		p->pipes[i] = malloc(sizeof(int) * 2);
		if (!p->pipes[i])
		{
			perror("[Pipex] Error: malloc pipe pair");
			exit_code(1);
		}
		if (pipe(p->pipes[i]) == -1)
		{
			perror("[Pipex] Error: pipe");
			exit_code(1);
		}
		i++;
	}
}

void	init_cmds(t_pipex *p, char *av[])
{
	int	i;

	p->cmds = malloc(sizeof(char *) * (p->nb_cmds + 1));
	if (!p->cmds)
	{
		perror("[Pipex] Error: malloc cmds");
		free_pipes(p);
		exit_code(1);
	}
	i = 0;
	while (i < p->nb_cmds)
	{
		if (p->here_doc == 0)
			p->cmds[i] = av[i + 2];
		else
			p->cmds[i] = av[i + 3];
		i++;
	}
	p->cmds[i] = NULL;
}

void	init_pids(t_pipex *p)
{
	p->pids = malloc(sizeof(pid_t) * p->nb_cmds);
	if (!p->pids)
	{
		perror("[Pipex] Error: pids malloc");
		free_struct(p);
		exit_code(1);
	}
}

void	init_struct(t_pipex *p)
{
	p->fd_infile = -1;
	p->fd_outfile = -1;
	p->nb_cmds = 0;
	p->here_doc = 0;
	p->pipes = NULL;
	p->pids = NULL;
	p->cmds = NULL;
	p->envp = NULL;
}

void	init_pipex(t_pipex *p, int ac, char *av[], char *envp[])
{
	init_struct(p);
	p->envp = envp;
	if (is_here_doc(av[1]))
	{
		p->here_doc = 1;
		p->nb_cmds = ac - 4;
	}
	else
	{
		p->nb_cmds = ac - 3;
		p->fd_infile = open_infile(av[1]);
	}
	p->fd_outfile = open_outfile(av[ac - 1], p);
	init_pipes(p);
	init_cmds(p, av);
	init_pids(p);
}
