/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/04/28 12:07:54 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		fd1;
	int		fd2;
	pid_t	pid;
	int		pipe_end[2];

	if (ac != 5)
		return (write(2, "Invalid number of arguments :/\n", 31));
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		error("An error ocurred opening the files\n");
	if (pipe(pipe_end) == -1)
		error("An error occured while creating the pipe\n");
	pid = fork();
	if (pid < 0)
		error("An error occuring while forking\n");
	if (!pid)
		child_process(fd1, pipe_end, av[2], envp);
	waitpid(pid, NULL, 0);
	parent_process(fd2, pipe_end, av[3], envp);
	return (0);
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