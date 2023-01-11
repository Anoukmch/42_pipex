/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:36:47 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/10 18:21:24 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **ag, char **envp)
{
	t_pipex	*pipex;

	if (ac != 5)
		error("Wrong input number", NULL);
	if (!envp[0])
		error("Paths not available", NULL);
	pipex = initialize(ag, envp);
	processes(pipex, envp);
	closing(pipex);
	waitpid(pipex->child1, NULL, 0);
	waitpid(pipex->child2, NULL, 0);
	freeing(pipex);
	return (0);
}
