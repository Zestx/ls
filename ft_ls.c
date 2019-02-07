/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:26:26 by qbackaer          #+#    #+#             */
/*   Updated: 2019/02/07 20:32:47 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 06:36:57 by qbackaer          #+#    #+#             */
/*   Updated: 2019/02/07 20:25:51 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursive_wpr(t_entry *entry, char *path, char *options)
{
	char		*subpath;
	
	if (S_ISDIR(entry->filestat.st_mode) && strcmp(entry->filename, "/"))
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
		printf("%s%s%s :\n", CYAN, dirpath, RESET);
	entries_list = NULL;
	dir_list = NULL;
	if ((dir = opendir(dirpath)) == NULL)
	{
		recursive += 1;
		perror("ERROR ");
		return (-1);
	}
	entries_list = generate_ll(entries_list, dir, dirpath, options);
	dir_list = browse_and_display(entries_list, dirpath, options);
	ptr = dir_list;
	while (ptr)
	{
		//printf("%s\n", ptr->filename);
		recursive_wpr(ptr, dirpath, options);
		ptr = ptr->next;
	}
	if (entries_list)
		free_list(entries_list);
	if (dir_list)
		free(dir_list);
	closedir(dir);
	return (0);
}

char	*parse_args(int argc, char **argv)
{
	int		i;
	int		j;
	int		opt_count;
	char	*opt_table;

	if ((opt_table = malloc(41)) == NULL)
		return (NULL);
	i = 1;
	opt_count = 0;
	while (i < argc && argv[i][0] == '-' && strcmp(argv[i], "--"))
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (!strchr(opt_table, argv[i][j]))
			{
				opt_table[opt_count] = argv[i][j];
				opt_table[opt_count + 1] = '\0';
				opt_count++;
			}
			j++;
		}
		i++;
	}
	return (opt_table);
}

int		check_opts(char *valid_opt, char *opt_table)
{

	while (*opt_table != '\0')
	{
		if (!strchr(valid_opt, *opt_table))
		{
			printf("error: -%c is not a valid options.\n", *opt_table);
			return (-1);
		}
		opt_table++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char	*options;

	options = NULL;
	if (argc > 1)
	{
		if (!(options = parse_args(argc, argv)))
			exit(EXIT_FAILURE);
		if (check_opts("Ralstr", options))
			exit(EXIT_FAILURE);
	}
	if (list("/etc", options, 0))
		exit(EXIT_FAILURE);
	return (0);
}
