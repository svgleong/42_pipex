/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:09:14 by svalente          #+#    #+#             */
/*   Updated: 2023/06/12 14:27:36 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

typedef struct s_fds
{
	int		fd1;
	int		fd2;
	int		pipe_end[2];
	int		std[2];
	char	**av;
	char	**cmds;
	char	*path;
}	t_fds;

t_fds	*fds(void);
void	error(char *str);
void	create_pipe(t_fds *fds, char **av, char **envp);
void	child_process1(t_fds *fds, int *pipe_end, char *cmd, char **envp);
void	child_process2(t_fds *fds, int *pipe_end, char *cmd, char **envp);
void	free_matrix(char **paths);
char	*find_path(char *cmd, char **envp);
void	close_fds(int fd1, int fd2);
void	execution_error(char *msg, t_fds *fds);
int		is_string_empty(const char *str);
void	error_handler(t_fds *fds, char *err_msg, int perr);
char	*check_access(char **paths, char *cmd);

#endif