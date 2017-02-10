 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstrelet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:56:49 by dstrelet          #+#    #+#             */
/*   Updated: 2017/02/09 13:17:00 by dstrelet         ###   ########.fr       */
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

# define RED        "\x1b[31m"
# define GREEN      "\x1b[32m"
# define YELLOW     "\x1b[33m"
# define BLUE       "\x1b[34m"
# define MAGENTA    "\x1b[35m"
# define CYAN       "\x1b[36m"
# define RESET      "\x1b[0m"
# define WHITE      "\033[0m"

typedef struct           flag_lis
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
    char    *timp;
    struct  passwd  *pw;
    struct  group   *gr;
    char    *permis;
    struct  d_lst  *next;
    int32_t         major;
    int32_t         minor;
}                        s_list;

// PROTOTIPURI
void print_ll(s_list *headd);
void print_name_by_list(s_list *temp);
void insert(struct dirent *d, char *path, char *str);
s_list *SortedMerge(s_list *a, s_list *b);
s_list *SortedMerget(s_list *a, s_list *b);
void FrontBackSplit(s_list *source,
        s_list **frontRef, s_list **backRef);
int ls(char *str);
void    print_l();
void print_name();
void error(char *str);
void reverse(s_list **head_ref);
void searchflag(char *str);
int     flag(char *str);
void fuckof(char str);
int in(char *str, char str2);
int minmin(char *str);
void MergeSort(s_list **headRef);
void    display_file(char *str);

//GLOBALE

flag_list   flaguri;
s_list      *head;
int  g_p;
int g_flagprove;

#endif
