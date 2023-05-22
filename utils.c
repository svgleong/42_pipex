/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:17 by svalente          #+#    #+#             */
/*   Updated: 2023/05/22 09:08:25 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	child_process1(int fd1, int fd2, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	dup2(fd1, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(fd1);
	close(fd2);
	close(pipe_end[0]);
	close(pipe_end[1]);
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (execve(path, cmds, envp) == -1)
	{
		free(path);
		free_matrix(cmds);
		close(0);
		close(1);
		error("command not found\n");
	}
}

void	child_process2(int fd1, int fd2, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(pipe_end[1]);
	close(pipe_end[0]);
	close(fd1);
	close(fd2);
	(void)fd1;
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (execve(path, cmds, envp) == -1)
	{
		free(path);
		free_matrix(cmds);
		close(0);
		close(1);
		error("command not found\n");
	}
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	int		j;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	cmd = ft_strjoin("/", cmd);
	j = 0;
	while (paths[j])
	{
		cmd_path = ft_strjoin(paths[j], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
			//break ;
		free(cmd_path);
		j++;
	}
	free_matrix(paths);
	return (cmd);
	/* if (access(cmd_path, F_OK) == -1)
	{
		//free(cmd_path);
		free_matrix(paths);
		return (cmd);
	} */
	//free(cmd);
	//return (cmd_path);
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
