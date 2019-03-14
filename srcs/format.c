/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:47:50 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/14 20:54:08 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	format_size(int size)
{
	char	*raw_size;
	int		nb_len;

	raw_size = ft_itoa(size);
	nb_len = ft_strlen(raw_size);
	while (10 - nb_len > 0)
	{
		ft_putchar(' ');
		nb_len++;
	}
	ft_putstr(raw_size);
	free(raw_size);
}

void	format_link(int link)
{
	char	*raw_link;
	int		nb_len;

	raw_link = ft_itoa(link);
	nb_len = ft_strlen(raw_link);
	while (3 - nb_len > 0)
	{
		ft_putchar(' ');
		nb_len++;
	}
	ft_putstr(raw_link);
	free(raw_link);
}

void	free_dirlist(char **dirlist)
{
	char *roam;

	if (!dirlist)
		return;
	roam = *dirlist;
	while (roam)
	{
		free(roam);
		roam++;
	}
	free(dirlist);
}
