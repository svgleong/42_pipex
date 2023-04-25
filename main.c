/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/04/21 14:31:13 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str);

int	main(int ac, char **av, char **envp)
{
	int 	fd1;
	int 	fd2;
	pid_t	pid;
	int		pipe_end[2];

	if (ac != 5)
		return (write(2, "Invalid number of arguments :/\n", 31));
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		error("An error ocurred opening the files\n");
	if (pipe(pipe_end) == -1);
		error("An error occured while creating the pipe\n");
	pid = fork();
	if (pid < 0);
		error("An error occuring while forking\n");
	if (!pid)
		child_process(fd1, pipe_end, av[2], envp);
	else
		parent_process(fd2, pipe_end, av[3], envp);
}

void	error(char *str)
{
	perror(str);
	exit(1);
}

int	child_process(int fd1, int *pipe_end, char *cmd, char **envp)
{
	char **cmds;
	
	dup2(fd1, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	cmds = ft_split(cmd, ' ');
	
}

const char	*find_path(char **cmds, char **envp)
{
	
}
