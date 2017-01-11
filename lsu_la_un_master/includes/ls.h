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
//# include <sys/acl.h>
//# include <uuid/uuid.h>
# include "libft.h"
typedef struct  s_elem
{
    char    *name;
    char    *path;
    time_t  date;
    mode_t  st_mode;
    nlink_t st_nlink;
    uid_t   st_uid;
    gid_t   st_gid;
    off_t   st_size;
    quad_t  st_blocks;
    dev_t   st_rdev;
    struct  s_elem  *next;
}               t_elem;


# endif