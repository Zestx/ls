/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 06:40:32 by qbackaer          #+#    #+#             */
/*   Updated: 2019/01/15 06:55:51 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//1.wrapper for display_entry. Rendered useless.
void	display_wpr(t_entry *entry, char *options)
{
	if (options && ft_strchr(options, 'l'))
		display_entry(entry->filename, &(entry->filestat), 1);
	else
		display_entry(entry->filename, &(entry->filestat), 0);
}

//2.display entries, and their stats if -l is set. Time stats displaying yet to do.
int		display_entry(char *fname, struct stat *fstats, int l_mode)
{
	if (l_mode == 1)
	{
		ft_putstr(get_mode(fstats->st_mode));
		ft_putstr(" ");
		printf("%hu", fstats->st_nlink);
		ft_putstr(" ");
		ft_putstr(get_usrname(fstats->st_uid));
		ft_putstr(" ");
		ft_putstr(get_grpname(fstats->st_gid));
		ft_putstr(" ");
		printf("%lld ", fstats->st_size);
		printf("%s\n", fname);
	}
	else if (l_mode == 0)
		printf("%s\n", fname);
	else
		return (-1);
	return (0);
}

//3.display all the nodes in a t_entry linked list. Use recursion if needed.
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
