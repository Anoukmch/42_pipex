/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:22 by amechain          #+#    #+#             */
/*   Updated: 2022/10/20 12:41:53 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_pipe(t_pipex	*pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd - 1)
	{
		if (pipe(pipex->ends + 2 * i) < 0)
			error ("Pipe failed", pipex);
		i++;
	}
}

void	here_doc(t_pipex *pipex, char **ag)
{
	int		file;
	char	*line;
	char	*temp;

	file = open("heredoc", O_CREAT | O_WRONLY
			| O_TRUNC, 0644);
	if (file < 0)
		error ("Open heredoc failed", pipex);
	temp = ft_strjoin(ag[2], "\n");
	ft_printf("Heredoc>");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		error ("Get_next_line failed", pipex);
	while (ft_strncmp(line, temp, (ft_strlen(temp) + 1)))
	{
		ft_putstr_fd(line, file);
		free(line);
		ft_printf("Heredoc>");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			error ("Get_next_line failed", pipex);
	}
	free(line);
	free(temp);
	close(file);
}

void	get_infile(t_pipex	*pipex, char **ag)
{
	if (pipex->cases == 0)
	{
		pipex->infile = open(ag[1], O_RDONLY);
		if (pipex->infile < 0)
			error ("Open infile failed", pipex);
	}
	else if (pipex->cases == 1)
	{
		here_doc(pipex, ag);
		pipex->infile = open("heredoc", O_RDONLY);
		if (pipex->infile < 0)
			error ("Open infile failed", pipex);
	}
}

void	get_outfile(t_pipex	*pipex, char *ag)
{
	if (pipex->cases == 0)
	{
		pipex->outfile = open(ag, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			error ("Open outfile failed", pipex);
	}
	else if (pipex->cases == 1)
		pipex->outfile = open(ag, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
}

t_pipex	*initialize(int count, int ac, char **ag, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	pipex->nbr_cmd = ac - 3 - count;
	pipex->cases = count;
	get_infile(pipex, ag);
	get_outfile(pipex, ag[ac - 1]);
	pipex->nbr_ends = 2 * (pipex->nbr_cmd - 1);
	pipex->ends = (int *)ft_calloc(pipex->nbr_ends, sizeof(int));
	pipex->path = use(envp);
	if (pipex->path)
	{
		pipex->paths = ft_split(pipex->path, ':');
		if (!pipex->paths)
			error ("Allocation failed", pipex);
	}
	create_pipe(pipex);
	if (!pipex || !pipex->ends)
		error ("Allocation failed", pipex);
	pipex->cmd = NULL;
	pipex->process = 0;
	pipex->process_id = 0;
	return (pipex);
}
