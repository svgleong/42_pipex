/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/06/12 14:38:48 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_fds *fds, char **av)
{
	fds->fd1 = -1;
	fds->fd2 = -1;
	fds->av = av;
	fds->cmds = NULL;
	fds->path = NULL;
	fds->pipe_end[0] = -1;
	fds->pipe_end[1] = -1;
}

int	main(int ac, char **av, char **envp)
{
	t_fds	fds;

	if (ac != 5)
		return (write(2, "Invalid number of arguments :/\n", 31));
	init_struct(&fds, av);
	if (is_string_empty(av[2]) && is_string_empty(av[3]))
	{
		ft_putstr_fd("Command \"\" not found\n", 2);
		return (1);
	}
	create_pipe(&fds, av, envp);
	return (0);
}

void	create_pipe(t_fds *fds, char **av, char **envp)
{
	pid_t	pid_1;
	pid_t	pid_2;

	pid_2 = 0;
	if (pipe(fds->pipe_end) == -1)
		error_handler(fds, "An error occured while creating the pipe", 1);
	pid_1 = fork();
	if (pid_1 == -1)
		error_handler(fds, "An error occured while forking", 1);
	if (pid_1 == 0)
	{
		child_process1(fds, fds->pipe_end, av[2], envp);
		return ;
	}
	pid_2 = fork();
	if (pid_2 == -1)
		error_handler(fds, "An error occured while forking", 1);
	if (pid_2 == 0)
	{
		child_process2(fds, fds->pipe_end, av[3], envp);
		return ;
	}
	close_fds(fds->pipe_end[0], fds->pipe_end[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
}
