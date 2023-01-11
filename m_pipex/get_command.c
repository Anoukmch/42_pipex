/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:08:45 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 16:31:32 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_relative(t_pipex	*pipex, char *raw_cmd)
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
			error ("Temp allocation failed", pipex);
		command = ft_strjoin(temp, raw_cmd);
		free(temp);
		if (!command)
			error ("Command allocation failed", pipex);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char	*get_command(t_pipex *pipex, char *raw_cmd)
{
	if (access(raw_cmd, 0) == 0)
		return (raw_cmd);
	return (get_command_relative(pipex, raw_cmd));
}
