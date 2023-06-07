/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:57:31 by svalente          #+#    #+#             */
/*   Updated: 2023/06/07 15:07:08 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	fds->fd1 = open(fds->av[1], O_RDONLY);
	if (fds->fd1 < 0)
	{
		perror("An error ocurred opening the infile");
		return ;
	}
	close(pipe_end[0]);
	if (dup2(fds->fd1, STDIN_FILENO) == -1)
		error_handler(fds, "Error redirecting in Child Process 1", 1);
	if (dup2(pipe_end[1], STDOUT_FILENO) == -1)
		error_handler(fds, "Error redirecting in Child Process 1", 1);
	close(pipe_end[1]);
	fds->cmds = ft_split(cmd, ' ');
	if (!fds->cmds)
		error_handler(fds, "Memory Error", 1);
	fds->path = find_path(ft_strdup(fds->cmds[0]), envp);
	if (!fds->path)
		error_handler(fds, "Memory Error", 1);
	if (execve(fds->path, fds->cmds, envp) == -1)
		execution_error("command 1 not found\n", fds);
	close_fds(fds->fd1, fds->fd2);
}

void	child_process2(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	fds->fd2 = open(fds->av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds->fd2 < 0)
	{
		perror("An error ocurred opening the outfile");
		return ;
	}
	close(pipe_end[1]);
	if (dup2(pipe_end[0], STDIN_FILENO) == -1)
		error_handler(fds, "Error redirecting in Child Process 2", 1);
	if (dup2(fds->fd2, STDOUT_FILENO) == -1)
		error_handler(fds, "Error redirecting in Child Process 2", 1);
	close(pipe_end[0]);
	fds->cmds = ft_split(cmd, ' ');
	if (!fds->cmds)
		error_handler(fds, "Memory Error", 1);
	fds->path = find_path(ft_strdup(fds->cmds[0]), envp);
	if (!fds->path)
		error_handler(fds, "Memory Error", 1);
	if (execve(fds->path, fds->cmds, envp) == -1)
		execution_error("command 2 not found\n", fds);
	close_fds(fds->fd1, fds->fd2);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*tmp;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	tmp = cmd;
	cmd = ft_strjoin("/", cmd);
	if (tmp)
		free(tmp);
	if (!cmd)
	{
		free_matrix(paths);
		return (NULL);
	}
	return (check_access(paths, cmd));
}

char	*check_access(char **paths, char *cmd)
{
	int		j;
	char	*cmd_path;

	j = 0;
	while (paths[j])
	{
		cmd_path = ft_strjoin(paths[j], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrix(paths);
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
		j++;
	}
	free_matrix(paths);
	return (cmd);
}
