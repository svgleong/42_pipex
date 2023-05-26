/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:17 by svalente          #+#    #+#             */
/*   Updated: 2023/05/26 16:20:58 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* t_fds	*fds(void)
{
	static t_fds	fds;

	return (&fds);
} */

void	error(char *str)
{
	(void) str;
	//perror(strerror(errno))
	//ft_putstr_fd(str, 2);
	perror(str);
	exit(EXIT_FAILURE);
}

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
	close(fd1);
	close(fd2);
}

void	execution_error(char *path, char **cmds, char *msg, t_fds *fds)
{
	(void)path;
	(void)cmds;
	(void)fds;
	free(path);
	free_matrix(cmds);
	if (ft_strncmp(msg, "command 1 not found", 19) == 0)
		close(fds->fd1);
	if (ft_strncmp(msg, "command 2 not found", 19) == 0)
		close(fds->fd2);
	error(msg);
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
