/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:45:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/01/21 19:25:33 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//1.return a new path from a current path and a subdirectory:
//ex:
//subdir_path("./directory", "subdirectory");
//will return "./directory/subdirectory"
char	*subdir_path(const char *current_path, const char *subdir)
{
	char	*full_path;
	int		i;
	int		j;

	if (!(full_path = malloc(strlen(current_path) + strlen(subdir) + 2)))
		return (NULL);
	i = 0;
	while (current_path[i] != '\0')
	{
		full_path[i] = current_path[i];
		i++;
	}
	full_path[i] = '/';
	i++;
	j = 0;
	while (subdir[j] != '\0')
	{
		full_path[i + j] = subdir[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

//2.free linked lists.
void	free_list(t_entry *entries)
{
	t_entry *tmp;

	if (!entries)
		return ;
	while (entries)
	{
		tmp = entries->next;
		free(entries);
		entries = tmp;
	}
	entries = NULL;
}
