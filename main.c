/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/05/31 12:00:23 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_fds	fds;

	fds.av = av;
	if (ac != 5)
		return (write(2, "Invalid number of arguments :/\n", 31));
	if (is_string_empty(av[2]) || is_string_empty(av[3]))
	{
		ft_putstr_fd("Command \"\" not found\n", 2);
		return (1);
	}
	create_pipe(&fds, av, envp);
	return (0);
}

void	create_pipe(t_fds *fds, char **av, char **envp)
{
	int		pipe_end[2];
	pid_t	pid_1;
	pid_t	pid_2;

	pid_2 = 0;
	if (pipe(pipe_end) == -1)
		perror("An error occured while creating the pipe");
	pid_1 = fork();
	if (pid_1 == -1)
		error("An error occured while forking");
	if (pid_1 == 0)
	{
		child_process1(fds, pipe_end, av[2], envp);
		return ;
	}
	pid_2 = fork();
	if (pid_2 == -1)
		error("An error occured while forking");
	if (pid_2 == 0)
	{
		child_process2(fds, pipe_end, av[3], envp);
		return ;
	}
	close_fds(pipe_end[0], pipe_end[1]);
	waitpid(pid_2, NULL, 0);
}
