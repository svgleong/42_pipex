/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:17 by svalente          #+#    #+#             */
/*   Updated: 2023/06/12 14:35:58 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	error(char *str)
// {
// 	perror(str);
// 	if (fds->fd1 != -1)
// 		close(fds->fd1);
// 	exit(EXIT_FAILURE);
// }

void	free_matrix(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	close_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	error_handler(t_fds *fds, char *err_msg, int perr)
{
	if (fds->fd1 != -1)
		close(fds->fd1);
	if (fds->fd2 != -1)
		close(fds->fd2);
	if (fds->std[0] != -1)
		close(fds->std[0]);
	if (fds->std[1] != -1)
		close(fds->std[1]);
	if (fds->cmds)
		free_matrix(fds->cmds);
	if (fds->path)
		free(fds->path);
	if (perr)
		perror(err_msg);
	else
		ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	execution_error(char *msg, t_fds *fds)
{
	if (ft_strncmp(msg, "command 1 not found", 19) == 0)
		close(fds->fd1);
	if (ft_strncmp(msg, "command 2 not found", 19) == 0)
		close(fds->fd2);
	error_handler(fds, msg, 0);
}

int	is_string_empty(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}
