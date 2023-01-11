/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:51:36 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 17:06:13 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# include "../includes/libs/libs.h"

typedef struct s_pipex
{
	pid_t	process;
	int		infile;
	int		outfile;
	int		*ends;
	int		cases;
	int		nbr_cmd;
	int		nbr_ends;
	char	**paths;
	char	**cmd;
	int		process_id;
	char	*path;

}				t_pipex;

int		main(int ac, char **ag, char **envp);
t_pipex	*initialize(int count, int ac, char **ag, char **envp);
void	get_outfile(t_pipex	*pipex, char *ag);
void	get_infile(t_pipex	*pipex, char **ag);
void	here_doc(t_pipex *pipex, char **ag);
void	create_pipe(t_pipex	*pipex);
char	*use(char **envp);
void	process(t_pipex	*pipex, char **envp, char **ag);
void	dupped_and_close(t_pipex	*pipex);
char	*get_command(t_pipex *pipex);
void	error(char *err, t_pipex *pipex);
void	freeing(t_pipex	*pipex);
void	closing(t_pipex	*pipex);
void	close_pipe(t_pipex	*pipex);
void	free_array(char **array);
char	*get_command_relative(t_pipex	*pipex);

#endif
