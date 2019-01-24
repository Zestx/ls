/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lklist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:22:09 by qbackaer          #+#    #+#             */
/*   Updated: 2019/01/23 17:51:21 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//This file contain the linked lists manipulation functions.

#include "ft_ls.h"

//1.Read the entries of a directory stream and create a linked list with those.
void	ll_read_create(t_entry **entry_list, DIR *dir, char *path, char *options)
{
	struct dirent	*entry;
	char			*new_path;
	while ((entry = readdir(dir)))
	{
		new_path = subdir_path(path, entry->d_name);
		if (entry->d_name[0] != '.' || (options && ft_strchr(options, 'a')))
			*entry_list = ll_append_node(*entry_list, ll_create_node(new_path, entry->d_name));
	}
}

//2.Append a new node to the queue of a linked list. If the list is empty (lst_head = null), it is initialized.
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

//3.Create a new node and fill it.
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
	node->filename = fname;
	node->filestat = st_buff;
	node->next = NULL;
	return(node);
}

//4.This functions wraps ll_create_node and ll_append node together.
t_entry	*ll_add_node(t_entry *lst_head, char *path, char *fname, int where)
{
	t_entry	*new_node;

	new_node = ll_create_node(path, fname);
	if (where == 0)
		lst_head = ll_append_node(lst_head, new_node);
	else
		lst_head = ll_append_node_h(lst_head, new_node);
	return (lst_head);
}

//5.Append a new node to a the head of a linked list. If the list is empty (lst_head = null), it is initialized.
t_entry *ll_append_node_h(t_entry *lst_head, t_entry *newnode)
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

//6.Count the number of elements(entries) in a list.
size_t	ll_count_nodes(t_entry *lst)
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
