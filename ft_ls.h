/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstrelet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:26:52 by dstrelet          #+#    #+#             */
/*   Updated: 2017/02/17 17:26:57 by dstrelet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/acl.h>
# include <sys/xattr.h>

typedef struct		s_flag_lis
{
	int			l;
	int			r_upper;
	int			a;
	int			r;
	int			t;
	int			u;
	int			f;
	int			g;
	int			d;
	int			m;
	int			g_upper;
	int			p;
}					t_flag_list;

typedef struct		s_t_lungimi
{
	int	nlink;
	int	pw_name;
	int	gr_name;
	int	size;
	int	timp;
	int	minor;
	int	major;
}					t_lungimi;

typedef struct		s_d_lst
{
	char			*name;
	char			*path;
	char			*parent;
	time_t			date;
	time_t			udate;
	int				i_am_from_the_dark_side;
	mode_t			st_mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	off_t			size;
	quad_t			blocks;
	dev_t			st_rdev;
	char			*timp;
	struct passwd	*pw;
	struct group	*gr;
	char			*permis;
	char			*linkof;
	int				p;
	char			acl;
	struct s_d_lst	*next;
	int32_t			major;
	int32_t			minor;
}					t_s_list;

void				print_ll(t_s_list *headd);
void				print_name_by_list(t_s_list *temp);
void				insert(struct dirent *d, char *path, char *str);
t_s_list			*sortedmerge(t_s_list *a, t_s_list *b);
// t_s_list			*sortedmerget(t_s_list *a, t_s_list *b);
void				frontbacksplit(t_s_list *source,
	t_s_list **frontref, t_s_list **backref);
void				print_l();
void				print_name();
char				*permis(struct stat *elem);
void				recurs(t_s_list *temp);
void				error(char *str);
void				reverse(t_s_list **head_ref);
void				searchflag(char *str);
int					flag(char *str);
void				stop(char str);
int					in(char *str, char str2);
int					minmin(char *str);
void				mine_mergesort(t_s_list **headref);
void				display_file(char *str);
void				filtreaza_path(char *str);
t_lungimi			antiponturi();
void				listdir(char *path);

t_flag_list			g_flaguri;
int					g_flagprove;
int					g_minmaj;

#endif
