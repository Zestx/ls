/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:59:56 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/14 20:24:24 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

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
		ft_putstr("  ");
		format_link(fstats->st_nlink);
		ft_putstr("  ");
		ft_putstr(get_usrname(fstats->st_uid));
		ft_putstr("  ");
		ft_putstr(get_grpname(fstats->st_gid));
		ft_putstr("  ");
		format_size(fstats->st_size);
		ft_putstr("  ");
		format_time(ctime(&(fstats->st_mtime)));
		ft_putstr(fname);
		ft_putchar('\n');
	}
	else if (l_mode == 0)
	{
		ft_putstr(fname);
		ft_putchar('\n');
	}
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
		if (options && ft_strchr(options, 'R'))
			recursive_wpr(cursor, dirpath, options);
		cursor = cursor->next;
	}
}

void	format_time(char *r_time)
{
	char	*f_time;
	int		col_count;
	char	*ptr;

	f_time = malloc(15);
	ptr = f_time;
	while (*r_time != ' ')
		r_time++;
	r_time++;
	col_count = 0;
	while (1)
	{
		if (*r_time == ':')
			col_count++;
		if (col_count >= 2)
			break ;
		*ptr = *r_time;
		ptr++;
		r_time++;
	}
	*ptr++ = ' ';
	*ptr = '\0';
	ft_putstr(f_time);
	free(f_time);
}
