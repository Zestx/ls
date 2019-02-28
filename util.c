/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:45:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/02/28 19:22:38 by qbackaer         ###   ########.fr       */
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

char	**update_dirmap(char **dirmap, char *directory)
{
	int		size;
	int		i;
	int		j;
	char	**upd_map;

	size = 0;
	if (dirmap)
		while (dirmap[size])
			size++;
	upd_map = malloc(sizeof(upd_map) * (size + 2));
	i = 0;
	while (dirmap)
	{
		upd_map[i] = malloc(ft_strlen(dirmap[i]) + 1);
		j = 0;
		while (dirmap[i][j] != '\0')
		{
			upd_map[i][j] = dirmap[i][j];
			j++;
		}
		upd_map[i][j] = '\0';
		i++;
		dirmap++;
	}
	j = 0;
	upd_map[i] = malloc(ft_strlen(directory) + 1);
	while (upd_map[i][j])
	{
		upd_map[i][j] = directory[j];
		j++;
	}
	upd_map[i][j] = '\0';
	upd_map[i + 1] = NULL;
	free(dirmap);
	return (upd_map);
}

void	free_dirmap(char **dirmap)
{
	char **tmp;

	tmp = dirmap;
	while (tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(dirmap);
}

char	*rm_trail_nl(char *str)
{
	int len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 2] == '\n')
		str[len - 2] = '\0';
	return (str);
}
