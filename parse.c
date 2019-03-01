/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:59:51 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/01 19:58:53 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse(int argc, char **argv, char *opt_table, char **dir_table)
{
	int i;
	int stop_opt;

	i = 1;
	stop_opt = 0;
	while (i < argc)
	{
		if (!strcmp("--", argv[i]))
		{
			stop_opt = 1;
			i++;
			continue;
		}
		if (!stop_opt && argv[i][0] == '-')
			opt_table = update_options(opt_table, argv[i]);
		else
			dir_table = update_dirs(dir_table, argv[i]);
		i++;
		printf("TABLE: %s\n", opt_table);
	}
	return (0);
}

char	*update_options(char *opt_table, char *new_opt)
{
	char	*upd_table;
	int i;
	int j;

	if (opt_table)
		upd_table = malloc(strlen(opt_table) + strlen(new_opt));
	else	
		upd_table = malloc(strlen(new_opt));
	i = 0;
	while (opt_table && i < strlen(opt_table))
	{
		upd_table[i] = opt_table[i];
		i++;
	}
	j = 1;
	while (j < strlen(new_opt))
	{
		upd_table[i] = new_opt[j];
		j++;
		i++;
	}
	upd_table[i] = '\0';
	return (upd_table);
}

char	**update_dirs(char **dir_table, char *new_dir)
{
	char **upd_table;

	return (upd_table);
}
