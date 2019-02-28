/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:59:56 by qbackaer          #+#    #+#             */
/*   Updated: 2019/02/27 19:57:23 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*rm_newline(char *str)
{
	int		i;
	char	*no_newline_cp;
	
	i = 0;
	no_newline_cp = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		no_newline_cp[i] = str[i];
		i++;
	}
	no_newline_cp[i] = '\0';
	return (no_newline_cp);
}

void	display_wpr(t_entry *entry, char *options)
{
	if (options && ft_strchr(options, 'l'))
		display_entry(entry->filename, &(entry->filestat), 1);
	else
		display_entry(entry->filename, &(entry->filestat), 0);
}

int		display_entry(char *fname, struct stat *fstats, int l_mode)
{
	if (l_mode == 1)
	{
		ft_putstr(get_mode(fstats->st_mode));
		//ft_putstr("  ");
		ft_putchar('\t');
		ft_putnbr(fstats->st_nlink);
		//ft_putstr("  ");
		ft_putchar('\t');
		ft_putstr(get_usrname(fstats->st_uid));
		//ft_putstr("  ");
		ft_putchar('\t');
		ft_putstr(get_grpname(fstats->st_gid));
		//ft_putstr("  ");
		ft_putchar('\t');
		ft_putnbr(fstats->st_size);
		//ft_putstr("  ");
		ft_putchar('\t');
		ft_putstr(rm_trail_nl(ctime(&(fstats->st_mtime))));
		//ft_putstr("  ");
		ft_putstr(fname);
		ft_putchar('\n');
	}
	else if (l_mode == 0)
		printf("%s\n", fname);
	else
		return (-1);
	return (0);
}

void	ll_display(t_entry *lst_head, char *dirpath, char *options)
{
	t_entry *cursor;

	cursor = lst_head;
	while (cursor)
	{
		display_wpr(cursor, options);
		if (options && strchr(options, 'R'))
			recursive_wpr(cursor, dirpath, options);
		cursor = cursor->next;
	}
}
