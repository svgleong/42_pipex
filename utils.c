/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:28:17 by svalente          #+#    #+#             */
/*   Updated: 2023/05/25 15:59:47 by svalente         ###   ########.fr       */
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
	//perror(strerror(errno));
	perror("mensagem erro");
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

void	execution_error(char *path, char **cmds, char *msg)
{
	free(path);
	free_matrix(cmds);
	error(msg);
	//write(2);
	//exit;
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
