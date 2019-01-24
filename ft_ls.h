/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:36:16 by qbackaer          #+#    #+#             */
/*   Updated: 2019/01/24 21:00:36 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define CMAG "\x1B[35m"
# define RESET "\x1B[0m"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include "./libft/libft.h"

typedef struct	s_entry
{
	char			*filename;
	struct stat		filestat;
	struct s_entry	*next;
}				t_entry;

typedef struct	s_cursors
{
	t_entry *wkst_c;
	t_entry *wkst_p;
	t_entry *curs_c;
	t_entry *curs_p;
}				t_ces, DIR *dir, char *dirpath, char *options)ursors;

//ft_ls.c
void			recursive_wpr(t_entry *entry, char *path, char *options);
int				list(char *dirpath, char *options, int recursive);
char			*parse_args(int argc, char **argv);
int				check_opts(char *valid_opt, char *opt_table);
//list.c
t_entry			*ll_append_node(t_entry *lst_head, t_entry *newnode);
t_entry			*ll_append_node_h(t_entry *lst_head, t_entry *newnode);
t_entry			*ll_create_node(char *path, char *fname);
t_entry			*ll_add_node(t_entry *lst_head, char *path, char *fname, int where);
size_t			ll_count_nodes(t_entry *lst);
//list_b.c
t_entry			*browse_and_display(t_entry *entries_list, char *dirpath, char *options);
t_entry			*generate_ll(t_entry *entries, DIR *dir, char *dirpath, char *options);

void			find_weakest_alpha(t_cursors *llc);
void			init_cursors(t_cursors *llc, t_entry *lst);
void			ll_display(t_entry *lst_head, char *dirpath, char *options);
void			ll_read_create(t_entry **entry_lisa, DIR *dir, char *path, char *options);
int				display_entry(char *fname, struct stat *fstat, int l_nmode);
char			*get_mode(mode_t file_mode);
char			*get_usrname(uid_t user_id);
char			*get_grpname(gid_t groupd_id);
void			get_type(char *buffer, mode_t file_mode);
void			get_perm(char *buffer, mode_t file_mode);
void			display_wpr(t_entry *entry, char *options);
t_entry			*newnode(char *path, char *filename);
char			*subdir_path(const char *current_path, const char *subdir);
void			free_list(t_entry *entries);
t_entry			*ll_alphasort(t_entry *lst, size_t ll_size, char *cwd);
t_entry			*ll_revrssort(t_entry *lst, char *cwd);

#endif
