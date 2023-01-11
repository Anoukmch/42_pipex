/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:06:27 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 17:01:11 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*initialize(char **ag, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	pipex->infile = open(ag[1], O_RDONLY);
	pipex->outfile = open(ag[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipex->path = use(envp);
	if (pipex->path)
	{
		pipex->paths = ft_split(pipex->path, ':');
		if (!pipex->paths)
			error ("Allocation failed", pipex);
	}
	pipex->raw_cmd1 = ft_split(ag[2], ' ');
	pipex->raw_cmd2 = ft_split(ag[3], ' ');
	if (!pipex || !pipex->raw_cmd1 || !pipex->raw_cmd2
		|| pipe(pipex->end) < 0 || pipex->infile < 0 || pipex->outfile < 0)
		error ("Initialization failed", pipex);
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	return (pipex);
}
