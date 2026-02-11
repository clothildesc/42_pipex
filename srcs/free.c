/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:24:57 by cscache           #+#    #+#             */
/*   Updated: 2025/06/23 11:18:29 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab_chars(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->pipes)
	{
		while (i < p->nb_cmds - 1)
		{
			if (p->pipes[i])
				free(p->pipes[i]);
			i++;
		}
		free(p->pipes);
	}
}

void	free_struct(t_pipex *p)
{
	free_pipes(p);
	if (p->cmds)
		free(p->cmds);
	if (p->pids)
		free(p->pids);
}

void	exit_code(int code)
{
	exit(code);
}
