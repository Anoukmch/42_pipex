/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:01:41 by amechain          #+#    #+#             */
/*   Updated: 2022/10/10 15:55:34 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	pid_t	child1;
	pid_t	child2;
	int		infile;
	int		outfile;
	int		end[2];
	char	*cmd1;
	char	*cmd2;
	char	*path;
	char	**paths;
	char	**raw_cmd1;
	char	**raw_cmd2;

}				t_pipex;

int		main(int ac, char **ag, char **envp);
void	closing(t_pipex	*pipex);
void	freeing(t_pipex	*pipex);
void	error(char *err, t_pipex *pipex);
char	*get_command(t_pipex *pipex, char *raw_cmd);
char	*use(char **envp);
t_pipex	*initialize(char **ag, char **envp);
void	free_array(char **array);
void	processes(t_pipex	*pipex, char **envp);
void	child_one(t_pipex	*pipex, char **envp);
void	child_two(t_pipex	*pipex, char **envp);
char	*get_command_relative(t_pipex	*pipex, char *raw_cmd);

#endif
