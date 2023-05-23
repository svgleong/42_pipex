/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:09:14 by svalente          #+#    #+#             */
/*   Updated: 2023/05/23 21:20:18 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./ft_printf/ft_printf.h"
# include "./Libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef	struct s_cmd
{	
	char			*cmd;
	char			*path;
	int				pipe_end[2];
	struct s_cmd	*next;
}	t_cmd;


void	error(char *str);
void	create_pipe(int	fd1, int fd2, char **av, char **envp);
void	child_process1(int fd1, int fd2, int *pipe_end, char *cmd, char **envp);
void	child_process2(int fd1, int fd2, int *pipe_end, char *cmd, char **envp);
void	free_matrix(char **paths);
char	*find_path(char *cmd, char **envp);

#endif