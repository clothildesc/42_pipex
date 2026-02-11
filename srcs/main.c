/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:38:06 by cscache           #+#    #+#             */
/*   Updated: 2025/06/26 10:02:03 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;
	int		code;

	if ((is_here_doc(av[1]) && ac < 6) \
	|| (!is_here_doc(av[1]) && ac < 5))
		return (write(2, "[Pipex] Error: invalid nb of arguments\n", 40), 1);
	init_pipex(&pipex, ac, av, envp);
	if (pipex.here_doc)
		handle_here_doc(&pipex, av[2]);
	code = pipe_and_fork(&pipex);
	return (code);
}
