/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:29:01 by qbackaer          #+#    #+#             */
/*   Updated: 2019/01/24 20:48:05 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		find_weakest_alpha(t_cursors *llc)
{
	while (llc->curs_c)
	{
		if (ft_strcmp(llc->wkst_c->filename, llc->curs_c->filename) > 0)
		{
			llc->wkst_c = llc->curs_c;
			llc->wkst_p = llc->curs_p;
		}
		llc->curs_p = llc->curs_c;
		llc->curs_c = llc->curs_c->next;
	}
}

void		init_cursors(t_cursors *llc, t_entry *lst)
{
	llc->curs_c = lst;
	llc->curs_p = llc->curs_c;
	llc->wkst_c = llc->curs_c;
	llc->wkst_p = llc->curs_p;
}

t_entry		*ll_alphasort(t_entry *lst, size_t ll_size, char *cwd)
{
	t_entry		*sorted_lst;
	t_cursors	llc;
	size_t		count;
	char		*path;

	sorted_lst = NULL;
	count = 0;
	while (count < ll_size - 1)
	{
		init_cursors(&llc, lst);
		find_weakest_alpha(&llc);
		path = subdir_path(cwd, llc.wkst_c->filename);
		sorted_lst = ll_add_node(sorted_lst, path, llc.wkst_c->filename, 0);
		if (llc.wkst_c == llc.wkst_p)
			lst = llc.wkst_c->next;
		else
			llc.wkst_p->next = llc.wkst_c->next;
		free(llc.wkst_c);
		count++;
	}
	path = subdir_path(cwd, lst->filename);
	sorted_lst = ll_add_node(sorted_lst, path, lst->filename, 0);
	free(lst);
	return (sorted_lst);
}

t_entry		*ll_revrssort(t_entry *lst, char *cwd)
{
	t_entry		*sorted_lst;
	t_cursors	llc;
	t_entry		*ptr;
	char		*path;

	sorted_lst = NULL;
	llc.curs_c = lst;
	while (llc.curs_c)
	{
		path = subdir_path(cwd, llc.curs_c->filename);
		sorted_lst = ll_add_node(sorted_lst, path, llc.curs_c->filename, 1);
		llc.curs_c = llc.curs_c->next;
	}
	free(lst);
	ptr = sorted_lst;
	return (sorted_lst);
}
