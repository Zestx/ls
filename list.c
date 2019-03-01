/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lklist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:22:09 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/01 16:54:30 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry	*ll_append_node(t_entry *lst_head, t_entry *newnode)
{
	t_entry	*ll_cursor;

	if (!newnode)
		return (NULL);
	if (!lst_head)
	{
		lst_head = newnode;
		return (lst_head);
	}
	ll_cursor = lst_head;
	while (ll_cursor->next)
	{
		ll_cursor = ll_cursor->next;
	}
	ll_cursor->next = newnode;
	return (lst_head);
}

t_entry	*ll_create_node(char *path, char *fname)
{
	t_entry		*node;
	struct stat	st_buff;

	if (!path || !fname)
		return (NULL);
	node = (t_entry*)malloc(sizeof(t_entry));
	if (!node)
		return (NULL);
	stat(path, &st_buff);
	node->filename = ft_strdup(fname);
	node->filestat = st_buff;
	node->next = NULL;
	return (node);
}

t_entry	*ll_add_node(t_entry *lst_head, char *path, char *fname, int where)
{
	t_entry	*new_node;

	new_node = ll_create_node(path, fname);
	if (!new_node)
	{
		printf("ERROR_ADDNODE\n");
		free(lst_head);
		exit(EXIT_FAILURE);
	}
	if (where == 0)
		lst_head = ll_append_node(lst_head, new_node);
	else
		lst_head = ll_append_node_h(lst_head, new_node);
	return (lst_head);
}

t_entry	*ll_append_node_h(t_entry *lst_head, t_entry *newnode)
{
	if (!newnode)
		return (NULL);
	if (!lst_head)
	{
		lst_head = newnode;
		if (lst_head)
			return (lst_head);
	}
	newnode->next = lst_head;
	lst_head = newnode;
	return (lst_head);
}

int		ll_count_nodes(t_entry *lst)
{
	t_entry	*cursor;
	size_t	ll_size;

	if (!lst)
		return (-1);
	cursor = lst;
	ll_size = 0;
	while (cursor)
	{
		cursor = cursor->next;
		ll_size++;
	}
	return (ll_size);
}
