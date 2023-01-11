/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:25 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 15:00:40 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	close_pipe(t_pipex	*pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_ends)
	{
		close(pipex->ends[i]);
		i++;
	}
}

void	closing(t_pipex	*pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	close_pipe(pipex);
}

void	freeing(t_pipex	*pipex)
{
	if (pipex->cmd)
		free_array(pipex->cmd);
	if (pipex->cases == 1)
		unlink("heredoc");
	free_array(pipex->paths);
	free(pipex->ends);
	free(pipex);
}

void	error(char *err, t_pipex *pipex)
{
	perror(err);
	if (pipex)
	{
		closing(pipex);
		freeing(pipex);
	}
	exit(1);
}
