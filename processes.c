/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:57:31 by svalente          #+#    #+#             */
/*   Updated: 2023/05/26 16:18:39 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	fds->fd1 = open(fds->av[1], O_RDONLY);
	if (fds->fd1 < 0)
		perror("An error ocurred opening the files");
	close(pipe_end[0]);
	dup2(fds->fd1, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[1]);
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (execve(path, cmds, envp) == -1)
		execution_error(path, cmds, "command 1 not found", fds);
	close_fds(fds->fd1, fds->fd2);
}

void	child_process2(t_fds *fds, int *pipe_end, char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	fds->fd2 = open(fds->av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds->fd2 < 0)
		perror("An error ocurred opening the files");
	close(pipe_end[1]);
	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fds->fd2, STDOUT_FILENO);
	close(pipe_end[0]);
	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (execve(path, cmds, envp) == -1)
		execution_error(path, cmds, "command 2 not found", fds);
	close_fds(fds->fd1, fds->fd2);
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
	return (cmd);
}	
//write(2, "cmd not found\n", ft_strlen("cmd not found\n"));
