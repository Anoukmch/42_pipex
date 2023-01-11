/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:07:57 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 14:59:18 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	closing(t_pipex	*pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->end[0]);
	close(pipex->end[1]);
}

void	freeing(t_pipex	*pipex)
{
	free_array(pipex->paths);
	free_array(pipex->raw_cmd1);
	free_array(pipex->raw_cmd2);
	free(pipex->cmd1);
	free(pipex->cmd2);
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
	exit (1);
}
