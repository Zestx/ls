/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:45:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/14 18:15:56 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*subdir_path(const char *current_path, const char *subdir)
{
	char	*full_path;
	int		i;
	int		j;

	if (!(full_path = malloc(ft_strlen(current_path) + ft_strlen(subdir) + 2)))
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
	t_entry *tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->filename);
		free(head);
		head = tmp;
	}
}

void	closedir_wpr(t_entry *entries, t_entry *dirlist, DIR *dir)
{
	if (entries)
		free_list(entries);
	if (dirlist)
		free_list(dirlist);
	if (closedir(dir) == -1)
	{
		perror("ERROR_CLOSEDIR ");
		exit(EXIT_FAILURE);
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

void	format_dirname(char *dirpath)
{
	ft_putstr(CYAN);
	ft_putstr(dirpath);
	ft_putstr(RESET);
	ft_putchar('\n');
}
