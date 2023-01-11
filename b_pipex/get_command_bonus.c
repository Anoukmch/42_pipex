/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:50 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 17:28:38 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_command_relative(t_pipex	*pipex)
{
	int		i;
	char	*command;
	char	*temp;

	i = 0;
	if (!pipex->paths)
		return (NULL);
	while (pipex->paths[i])
	{
		temp = ft_strjoin(pipex->paths[i], "/");
		if (!temp)
			error ("Allocation failed", pipex);
		command = ft_strjoin(temp, pipex->cmd[0]);
		free(temp);
		if (!command)
			error ("Allocation failed", pipex);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char	*get_command(t_pipex *pipex)
{
	if (access(pipex->cmd[0], 0) == 0)
		return (pipex->cmd[0]);
	return (get_command_relative(pipex));
}
