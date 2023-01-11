/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:25:13 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/10 15:11:04 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **ag, char **envp)
{
	t_pipex	*pipex;
	int		count;

	count = 0;
	if (!envp[0])
		error("Paths not available", NULL);
	if (ac >= 6 && !ft_strncmp("here_doc", ag[1], 9))
		count = 1;
	else if (ac >= 5)
		count = 0;
	else
		error ("Wrong number of arguments", NULL);
	pipex = initialize(count, ac, ag, envp);
	while (pipex->process_id < pipex->nbr_cmd)
	{
		process(pipex, envp, ag);
		pipex->process_id++;
	}
	closing(pipex);
	waitpid(-1, NULL, 0);
	while (wait(NULL) != -1)
		continue ;
	freeing(pipex);
	return (0);
}
