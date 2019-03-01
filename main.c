/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:09:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/03/01 19:53:26 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *opt_table;
	char **dir_table;

	parse(argc, argv, opt_table, dir_table);
	printf("OPTIONS: %s\n", opt_table);
	return (0);
}
