/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 06:36:57 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/14 18:03:07 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	recursive_wpr(t_entry *entry, char *path, char *options)
{
	char		*subpath;

	if (S_ISDIR(entry->filestat.st_mode) && ft_strcmp(entry->filename, "/"))
	{
		subpath = subdir_path(path, entry->filename);
		list(subpath, options, 1);
		free(subpath);
	}
}

int		list(char *dirpath, char *options, int recursive)
{
	DIR			*dir;
	t_entry		*entries_list;
	t_entry		*ptr;
	t_entry		*dir_list;

	if (recursive)
		format_dirname(dirpath);
	entries_list = NULL;
	dir_list = NULL;
	if ((dir = opendir(dirpath)) == NULL)
	{
		recursive += 1;
		ft_putchar('\n');
		return (-1);
	}
	entries_list = generate_ll(entries_list, dir, dirpath, options);
	dir_list = browse_and_display(entries_list, dirpath, options);
	ptr = dir_list;
	while (ptr)
	{
		recursive_wpr(ptr, dirpath, options);
		ptr = ptr->next;
	}
	closedir_wpr(entries_list, dir_list, dir);
	return (0);
}

int		check_opts(char *valid_opt, char *opt_table)
{
	if (opt_table == NULL)
	{
		opt_table = malloc(2);
		opt_table[0] = '0';
		opt_table[1] = '\0';
	}
	while (*opt_table != '\0')
	{
		if (!ft_strchr(valid_opt, *opt_table))
		{
			ft_putstr("error: invalid options.\n");
			return (-1);
		}
		opt_table++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char	*opt_table;
	char	**dir_table;

	opt_table = NULL;
	dir_table = NULL;
	parse(argc, argv, &opt_table, &dir_table);
	if (check_opts("0Ralstr", opt_table))
		exit(EXIT_FAILURE);
	if (dir_table)
		while (**dir_table != '\0')
		{
			list(*dir_table, opt_table, 0);
			dir_table++;
		}
	else
		list(".", opt_table, 0);
	return (0);
}
