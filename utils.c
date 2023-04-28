/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:17 by svalente          #+#    #+#             */
/*   Updated: 2023/04/28 15:22:32 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(1);
}

void	child_process(int fd1, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;
	
	dup2(fd1, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	cmds = ft_split(cmd, ' ');
	//printf("cmd: :%s:\n", cmds[0]);
	//printf("cmd: :%s:\n", cmds[1]);
	path = find_path(cmds[0], envp);
	//printf("path: %s\n", path);
	if (execve(path, cmds, envp) == -1)
	{
		free_matrix(cmds);
		error("command not found1\n");
	}
}

void	parent_process(int fd2, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;
	
	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(pipe_end[1]);
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (execve(path, cmds, envp) == -1)
	{
		free_matrix(cmds);
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
	//printf("entrei\n");
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	//cmd = *ft_split(cmd, ' ');
	cmd = ft_strjoin("/", cmd);
	//printf("cmd/: %s\n", cmd);
	j = 0;
	while (paths[j])
	{
		cmd_path = ft_strjoin(paths[j], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			break ;
			//return (cmd_path);
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
