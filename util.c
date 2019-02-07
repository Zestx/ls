/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:45:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/02/07 20:42:08 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	free_list(t_entry *head)
{
	t_entry *node;

	if (!head)
		return ;
	node = head;
	while (node)
	{
		free(node);
		node = node->next;
	}
}

void	ll_read_create(t_entry **entries, DIR *dir, char *path, char *options)
{
	struct dirent	*entry;
	char			*new_path;
	
	new_path = NULL;
	while ((entry = readdir(dir)))
	{
		new_path = subdir_path(path, entry->d_name);
		if (entry->d_name[0] != '.' || (options && ft_strchr(options, 'a')))
			*entries =
			ll_append_node(*entries, ll_create_node(new_path, entry->d_name));
		free(new_path);
	}
}
