/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/05/20 10:53:19 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		fd1;
	int		fd2;

	if (ac != 5)
		return (write(2, "Invalid number of arguments :/\n", 31));
	/* if (ft_strncmp(av[2], "", 2) == 0 || ft_strncmp(av[3], "", 2) == 0)
		return (write(2, "Empty commands\n", 15)); */
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		error("An error ocurred opening the files\n");
	create_pipe(fd1, fd2, av, envp);
	close(fd1);
	close(fd2);
}

void	create_pipe(int fd1, int fd2, char **av, char **envp)
{
	int		pipe_end[2];
	pid_t	pid_1;
	pid_t	pid_2;

	pid_2 = 0;
	if (pipe(pipe_end) == -1)
		perror("An error occured while creating the pipe\n");
	pid_1 = fork();
	if (pid_1 == -1)
		error("An error occuring while forking\n"); //perror or error?
	if (pid_1 == 0)
		child_process1(fd1, fd2 , pipe_end, av[2], envp);
	if (pid_1 > 0)
	{
		//waitpid(pid_1, NULL, 0);
		pid_2 = fork();
		if (pid_2 == -1)
			error("An error occuring while forking\n");
		if (pid_2 == 0)
			child_process2(fd1, fd2, pipe_end, av[3], envp);
	}
	close(pipe_end[0]);
	close(pipe_end[1]);
	waitpid(pid_2, NULL, 0);
	close(fd1);
	close(fd2);
}

/* int main(int ac, char **av)
{
	(void)ac;
	char **cmds = ft_split(av[1], ' ');
	char *cmd = *ft_split(av[1], ' ');
	int i = 0;

	while (cmds[i])
	{
		printf("cmd[%d]: %s\n", i, cmds[i]);
		i++;
	}
	printf("cmd alone: %s\n", cmd);
	free(cmd);
	free_matrix(cmds);
} */