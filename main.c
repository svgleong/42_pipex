/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/05/25 14:53:56 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	//int		fdd;
	//int		fd2;
	t_fds	fds;
	
	if (ac != 5)
		return (write(2, "Invalid number of arguments :/\n", 31));
	if (is_string_empty(av[2]) || is_string_empty(av[3]))
	{
		perror("Empty command or commands");
		return 0;
	}
	fds.fd1 = open(av[1], O_RDONLY);
	fds.fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds.fd1 < 0 || fds.fd2 < 0)
		perror("An error ocurred opening the files"); //with p the xcvbn cat ls out works but the exit code is incorrect...
	create_pipe(&fds, av, envp);
	//close(fds.fd1);
	//close(fds.fd2);
	/* for (int i = 0; i < 30; i++)
	{
		fdd = open(av[1], O_RDONLY);
		printf("fdd number: %d\n", fdd);
	} */
}

void	create_pipe(t_fds *fds, char **av, char **envp)
{
	int		pipe_end[2];
	pid_t	pid_1;
	pid_t	pid_2;

	pid_2 = 0;
	if (pipe(pipe_end) == -1)
		perror("An error occured while creating the pipe"); //perror or error?
	pid_1 = fork();
	if (pid_1 == -1)
		error("An error occuring while forking"); 
	if (pid_1 == 0) {
		
	} // && fds->fd1 >= 0)
		child_process1(fds, pipe_end, av[2], envp);
	//waitpid(pid_1, NULL, 0); //with waitpid /dev/random doesn't work
	pid_2 = fork();
	if (pid_2 == -1)
		error("An error occuring while forking\n");
	if (pid_2 == 0) // && fds->fd2 >= 0)
		child_process2(fds, pipe_end, av[3], envp);
	close_fds(pipe_end[0], pipe_end[1]);
	waitpid(pid_2, NULL, 0);
	close_fds(fds->fd1, fds->fd2);
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