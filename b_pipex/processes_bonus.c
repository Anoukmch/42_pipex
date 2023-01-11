/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:01:38 by amechain          #+#    #+#             */
/*   Updated: 2022/11/02 14:23:06 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dupped_and_close(t_pipex	*pipex)
{
	if (pipex->process_id == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) < 0)
			error ("Dup2 failed", pipex);
		if (dup2(pipex->ends[1], STDOUT_FILENO) < 0)
			error ("Dup2 failed", pipex);
	}
	else if (pipex->process_id == pipex->nbr_cmd - 1)
	{
		if (dup2(pipex->ends[2 * pipex->process_id - 2], STDIN_FILENO) < 0)
			error ("Dup2 failed", pipex);
		if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
			error ("Dup2 failed", pipex);
	}
	else
	{
		if (dup2(pipex->ends[2 * pipex->process_id - 2], STDIN_FILENO) < 0)
			error ("Dup2 failed", pipex);
		if (dup2(pipex->ends[2 * pipex->process_id + 1], STDOUT_FILENO) < 0)
			error ("Dup2 failed", pipex);
	}
	close_pipe(pipex);
}

void	process(t_pipex	*pipex, char **envp, char **ag)
{
	char	*command;

	pipex->process = fork();
	if (pipex->process < 0)
		error ("Fork failed", pipex);
	else if (pipex->process == 0)
	{
		dupped_and_close(pipex);
		pipex->cmd = ft_split(ag[2 + pipex->process_id + pipex->cases], ' ');
		if (!pipex->cmd)
			error ("Allocation failed", pipex);
		command = get_command(pipex);
		if (!command)
			error ("Command doesn't exists", pipex);
		if (execve(command, pipex->cmd, envp) < 0)
		{
			free(command);
			error ("Execve failed", pipex);
		}
		free_array(pipex->cmd);
		free(command);
		pipex->cmd = NULL;
	}
}
