/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:09:45 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 17:20:04 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_two(t_pipex	*pipex, char **envp)
{
	close(pipex->infile);
	close(pipex->end[1]);
	if (dup2(pipex->end[0], STDIN_FILENO) < 0)
		error ("Dup2 failed", pipex);
	close(pipex->end[0]);
	if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
		error ("Dup2 failed", pipex);
	close(pipex->outfile);
	pipex->cmd2 = get_command(pipex, pipex->raw_cmd2[0]);
	if (!pipex->cmd2)
		error ("Command doesn't exists or wrong paths", pipex);
	if (execve(pipex->cmd2, pipex->raw_cmd2, envp) < 0)
		error ("Execve failed", pipex);
}

void	child_one(t_pipex	*pipex, char **envp)
{
	close(pipex->outfile);
	close(pipex->end[0]);
	if (dup2(pipex->infile, STDIN_FILENO) < 0)
		error ("Dup2 failed", pipex);
	close(pipex->infile);
	if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
		error ("Dup2 failed", pipex);
	close(pipex->end[1]);
	pipex->cmd1 = get_command(pipex, pipex->raw_cmd1[0]);
	if (!pipex->cmd1)
		error ("Command doesn't exists or wrong paths", pipex);
	if (execve(pipex->cmd1, pipex->raw_cmd1, envp) < 0)
		error ("Execve failed", pipex);
}

void	processes(t_pipex	*pipex, char **envp)
{
	pipex->child1 = fork();
	if (pipex->child1 < 0)
		error ("Fork failed", pipex);
	else if (pipex->child1 == 0)
		child_one(pipex, envp);
	pipex->child2 = fork();
	if (pipex->child2 < 0)
		error ("Fork failed", pipex);
	else if (pipex->child2 == 0)
		child_two(pipex, envp);
}
