/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstrelet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:56:49 by dstrelet          #+#    #+#             */
/*   Updated: 2016/12/28 16:56:50 by dstrelet         ###   ########.fr       */
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

typedef struct           flag_list
{
     int l;
     int r_upper;
     int a;
     int r;
     int t;
     int u;
     int f;
     int g;
     int d;
     int m;
     int g_upper;
     int p;
}                        flag_list;

typedef struct      d_lst
{
    char    *name;
    char    *path;
    char    *parent;
    time_t  date;
    mode_t  st_mode;
    nlink_t nlink;
    uid_t   uid;
    gid_t   gid;
    off_t   size;
    quad_t  blocks;
    dev_t   st_rdev;
    char    *datee;
    struct  passwd  *pw;
    struct  group   *gr;
    char    *permis;
    struct  s_elem  *next;
}                        s_list;

#endif