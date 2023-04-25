/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:14 by svalente          #+#    #+#             */
/*   Updated: 2023/04/25 14:44:43 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str);
void	child_process(int fd1, int *pipe_end, char *cmd, char **envp);
void	parent_process(int fd2, int *pipe_end, char *cmd, char **envp);
void	free_matrix(char **paths);
const char	*find_path(char *cmd, char **envp);

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
	if (pipe(pipe_end) == -1)
		error("An error occured while creating the pipe\n");
	pid = fork();
	if (pid < 0)
		error("An error occuring while forking\n");
	if (!pid)
		child_process(fd1, pipe_end, av[2], envp);
	else
		parent_process(fd2, pipe_end, av[3], envp);
	return (0);
}

void	error(char *str)
{
	perror(str);
	exit(1);
}

void	child_process(int fd1, int *pipe_end, char *cmd, char **envp)
{
	char **cmds;
	
	dup2(fd1, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	cmds = ft_split(cmd, ' ');
	if (execve(find_path(cmd, envp), cmds, envp) == -1)
		exit(1);
}

void	parent_process(int fd2, int *pipe_end, char *cmd, char **envp)
{
	char **cmds;
	
	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(pipe_end[1]);
	cmds = ft_split(cmd, ' ');
	if (execve(find_path(cmd, envp), cmds, envp) == -1)
		exit(1);
}


const char	*find_path(char *cmd, char **envp)
{
	int		i;
	int		j;
	char	*full_path;
	char 	**paths;
	char	*cmd_path;
	
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	full_path = envp[i] + 5;
	paths = ft_split(full_path, ':');
	cmd = ft_strjoin("/", cmd);
	j = 0;
	while (paths[j])
	{
		cmd_path = ft_strjoin(paths[j], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		j++;
	}
	free(cmd);
	free_matrix(paths);
	return (cmd_path);
}

void	free_matrix(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/* int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	const char *path;

	path = find_path("ls", envp);

	printf("found path: %s\n", path);
	free((void *)path);
} */
