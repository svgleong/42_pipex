/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:57:31 by svalente          #+#    #+#             */
/*   Updated: 2023/06/14 12:24:50 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	fds->cmds = ft_split(cmd, ' ');
	if (!fds->cmds)
		error_handler(fds, "Memory Error", 1);
	if (fds->cmds[0])
	{
		fds->path = find_path(ft_strdup(fds->cmds[0]), envp, fds);
		if (!fds->path)
			error_handler(fds, "Memory error", 1);
	}
	else
		error_handler(fds, "command 1 not found\n", 2);
	close(pipe_end[0]);
	fds->std[0] = dup2(fds->fd1, STDIN_FILENO);
	if (fds->std[0] == -1)
		error_handler(fds, "Error redirecting in Child Process 1", 1);
	fds->std[1] = dup2(pipe_end[1], STDOUT_FILENO);
	if (fds->std[1] == -1)
		error_handler(fds, "Error redirecting in Child Process 1", 1);
	close(pipe_end[1]);
	if (execve(fds->path, fds->cmds, envp) == -1)
		execution_error("command 1 not found\n", fds);
	close_fds(fds->fd1, fds->fd2);
}

void	child_process2(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	fds->cmds = ft_split(cmd, ' ');
	if (!fds->cmds)
		error_handler(fds, "Memory Error", 1);
	if (fds->cmds[0])
	{
		fds->path = find_path(ft_strdup(fds->cmds[0]), envp, fds);
		if (!fds->path)
			error_handler(fds, "Memory error", 1);
	}
	else
		error_handler(fds, "command 2 not found\n", 2);
	close(pipe_end[1]);
	fds->std[0] = dup2(pipe_end[0], STDIN_FILENO);
	if (fds->std[0] == -1)
		error_handler(fds, "Error redirecting in Child Process 2", 1);
	fds->std[1] = dup2(fds->fd2, STDOUT_FILENO);
	if (fds->std[1] == -1)
		error_handler(fds, "Error redirecting in Child Process 2", 1);
	close(pipe_end[0]);
	if (execve(fds->path, fds->cmds, envp) == -1)
		execution_error("command 2 not found\n", fds);
	close_fds(fds->fd1, fds->fd2);
}

char	*find_path(char *cmd, char **envp, t_fds *fds)
{
	int		i;
	char	**paths;
	char	*tmp;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
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
	return (check_access(paths, cmd, fds));
}

char	*check_access(char **paths, char *cmd, t_fds *fds)
{
	int		j;
	char	*cmd_path;

	j = 0;
	while (paths[j])
	{
		cmd_path = ft_strjoin(paths[j], cmd);
		if (!cmd_path)
			error_handler(fds, "Memory Error", 1);
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
	free(cmd);
	error_handler(fds, "command not found\n", 2);
	return (NULL);
}
