/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:57:31 by svalente          #+#    #+#             */
/*   Updated: 2023/05/25 15:55:13 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	close(pipe_end[0]);
	dup2(fds->fd1, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[1]);
	close_fds(fds->fd1, fds->fd2);
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (execve(path, cmds, envp) == -1)
		execution_error(path, cmds, "command 1 not found");
}

void	child_process2(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	close(pipe_end[1]);
	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fds->fd2, STDOUT_FILENO);
	close(pipe_end[0]);
	close_fds(fds->fd1, fds->fd2);
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	
	//if (execve("/bin/lsz", cmds, envp) == -1)
	//	execution_error(path, cmds, "command 2 not found");
	
	if (execve(path, cmds, envp) == -1)
		execution_error(path, cmds, "command 2 not found");
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	int		j;
	char	**paths;
	char	*cmd_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
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
		free(cmd_path);
		j++;
	}
	free_matrix(paths);

	write(2, "cmd not found\n", ft_strlen("cmd not found\n"));
	
	return (cmd);
}
