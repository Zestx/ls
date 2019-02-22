/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:32:42 by qbackaer          #+#    #+#             */
/*   Updated: 2019/02/15 14:39:58 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry	*generate_ll(t_entry *entries, DIR *dir, char *dirpath, char *options)
{
	int lst_size;

	lst_size = 1;
	ll_read_create(&entries, dir, dirpath, options);
	lst_size = ll_count_nodes(entries);
	if (lst_size <= 0)
		return (NULL);
	entries = ll_alphasort(entries, lst_size, dirpath);
	if (options && strchr(options, 'r'))
		entries = ll_revrssort(entries, dirpath);
	return (entries);
}

t_entry	*browse_and_display(t_entry *entries_list, char *dirpath, char *options)
{
	t_entry *ptr;
	t_entry *dir_list;
	char 	*subdir;

	dir_list = NULL;
	ptr = entries_list;
	while (ptr)
	{
		if (options && strchr(options, 'R') && S_ISDIR(ptr->filestat.st_mode))
		{
			if (ft_strcmp(".", ptr->filename) && ft_strcmp("..", ptr->filename))
			{
				subdir = subdir_path(dirpath, ptr->filename);
				dir_list = ll_add_node(dir_list, subdir, ptr->filename, 0);
				free(subdir);

			}	
		}
		display_wpr(ptr, options);
		ptr = ptr->next;
	}
	ft_putchar('\n');
	return (dir_list);
}
/*
t_tolist *add_tolist(t_tolist *head, char *dirname)
{
	t_tolist *newnode;

	if (!dirname)
		return (NULL);
}*/
