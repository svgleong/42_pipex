/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:21:15 by svalente          #+#    #+#             */
/*   Updated: 2023/05/23 22:31:39 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*new_node(char *av, char **envp)
{
	t_cmd	*new;
	int		i;
	
	i = 0;
	new = malloc(sizeof(t_cmd));
	if(!new)
		return (0);
	new->cmd = av;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	new->path = ft_split(envp[i] + 5, ':');
	new->next = NULL;
	return (new);
}

t_cmd	*last_cmd(t_cmd *lst)
{
	if(!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_cmd **lst, t_cmd *new)
{
	
}