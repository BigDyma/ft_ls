#ifndef LS_H
# define LS_H
# include <dirent.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <stdlib.h>
//# include <sys/acl.h>
//# include <uuid/uuid.h>
# include "libft.h"

typedef struct  s_elem
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
}               t_elem;

typedef struct  s_flag
{
    int l;
    int a;
    int r;
    int R;
    int t;
}               t_flag;

void    error(char *str);
# endif