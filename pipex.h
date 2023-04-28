/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:09:14 by svalente          #+#    #+#             */
/*   Updated: 2023/04/28 11:32:21 by svalente         ###   ########.fr       */
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

void	error(char *str);
void	child_process(int fd1, int *pipe_end, char *cmd, char **envp);
void	parent_process(int fd2, int *pipe_end, char *cmd, char **envp);
void	free_matrix(char **paths);
char	*find_path(char *cmd, char **envp);

#endif