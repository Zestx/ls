/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:59:51 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/14 18:04:09 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		parse(int argc, char **argv, char **opt_table, char ***dir_table)
{
	int i;
	int stop_opt;

	i = 1;
	stop_opt = 0;
	while (i < argc)
	{
		if (!ft_strcmp("--", argv[i]))
		{
			stop_opt = 1;
			i++;
			continue;
		}
		if (!stop_opt && argv[i][0] == '-')
			*opt_table = update_options(*opt_table, argv[i]);
		else
			*dir_table = update_dirs(*dir_table, argv[i]);
		i++;
	}
	return (0);
}

char	*update_options(char *opt_table, char *new_opt)
{
	char	*upd_table;
	size_t	i;
	size_t	j;

	if (opt_table)
		upd_table = malloc(ft_strlen(opt_table) + ft_strlen(new_opt));
	else
		upd_table = malloc(ft_strlen(new_opt));
	i = 0;
	while (opt_table && i < ft_strlen(opt_table))
	{
		upd_table[i] = opt_table[i];
		i++;
	}
	j = 1;
	while (j < ft_strlen(new_opt))
	{
		upd_table[i] = new_opt[j];
		j++;
		i++;
	}
	upd_table[i] = '\0';
	if (opt_table)
		free(opt_table);
	return (upd_table);
}

char	**update_dirs(char **dir_table, char *new_dir)
{
	char	**upd_table;
	char	**ptr;
	int		dir_size;
	int		tab_size;

	dir_size = ft_strlen(new_dir);
	tab_size = get_dirtable_size(dir_table);
	upd_table = malloc(sizeof(upd_table) * (tab_size + 2));
	ptr = upd_table;
	while (tab_size && **dir_table != '\0')
	{
		*ptr = malloc(ft_strlen(*dir_table) + 1);
		ft_strcpy(*ptr, *dir_table);
		dir_table++;
		ptr++;
	}
	*ptr = malloc(dir_size + 1);
	ft_strcpy(*ptr, new_dir);
	*(ptr + 1) = malloc(1);
	**(ptr + 1) = '\0';
	free_dirtable(dir_table);
	return (upd_table);
}

int		get_dirtable_size(char **dir_table)
{
	int		size;
	char	**roam;

	if (!dir_table)
		return (0);
	size = 0;
	roam = dir_table;
	while (**roam != '\0')
	{
		size++;
		roam++;
	}
	return (size);
}

void	free_dirtable(char **dir_table)
{
	char **roam;

	if (!dir_table)
		return ;
	roam = dir_table;
	while (**roam != '\0')
	{
		free(*roam);
		roam++;
	}
	free(dir_table);
}
