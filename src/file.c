/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstrelet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:56:38 by dstrelet          #+#    #+#             */
/*   Updated: 2016/12/28 16:56:40 by dstrelet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
typedef struct 		flag_list
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
}					flag_list;

typedef struct		s_list
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
}					d_lst;

flag_list flaguri;
d_lst	head;

void push(s_list	**head_ref, char  *new_data)
{
	s_list* new_node = (s_list*)malloc(sizeof(s_list));
	new_node->drum = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void append(s_list **head_ref, char* new_data)
{
	s_list *new_node = (s_list*)malloc(sizeof(s_list));
	s_list *last = *head_ref;
	new_node->drum = new_data;
	new_node->next = NULL;

	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}
	while (last->next != NULL)
	{
		*head_ref = new_node;
		return;
	}
	last->next = new_node;
	return;
}

int		check(char *str)
{
	int i = 0;
	size_t min = 1;
	while (str[i])
	{
		if (str[i] == '-')
			min--;
		i++;
	}
	return ((str[0] == '-' && str[1]) && !min);
}

int in(char *str, char str2)
{
	int i = 0;
	while (str[i])
	{
		if (str2 == str[i])
			return (1);
		i++;
	}
	return (0);
}

int is_dot(char *str)
{
	return (str[0] == '.');
}

void printList(s_list *ptr)
{
    while (ptr != NULL)
    {
        printf("%s->", ptr->drum);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

void l_flag(char *str)
{
	struct dirent 	*d;
	DIR 			*dir;
	struct stat fileStat;
	char fullpath[256];
	char mtime[100];
	if ((dir = opendir(str)) == NULL)
		return;
	while ((d = readdir(dir)))
	{
		if (is_dot(d->d_name))
			continue;
		strcpy (fullpath, str);
        strcat (fullpath, "/");
        strcat (fullpath, d->d_name);
        if (stat(fullpath, &fileStat))
        	perror(fullpath);
        else
        {
          printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
          printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
          printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
          printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
          printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
          printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
          printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
          printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
          printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
          printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
          strcpy(mtime, ctime(&fileStat.st_mtime));
          printf("\t%s",mtime);
        }
       	printf("%s\t", d->d_name);
        printf("\n");  
	}
	return;
}

void done(char *str)
{
	int i = 1;
	while (str[i])
	{
		if (in("lRarGtufgdmp", str[i]))
		{
			flaguri.l = (str[i] == 'l') ? 1 : flaguri.l;	
			flaguri.r_upper = (str[i] == 'R') ? 1 : flaguri.r_upper;
			flaguri.a = (str[i] == 'a') ? 1 : flaguri.a;
			flaguri.r = (str[i] == 'r') ? 1 : flaguri.r;
			flaguri.t = (str[i] == 't') ? 1 : flaguri.t;
			flaguri.u = (str[i] == 'u') ? 1 : flaguri.u;
			flaguri.f = (str[i] == 'f') ? 1 : flaguri.f;
			flaguri.g = (str[i] == 'g') ? 1 : flaguri.g;
			flaguri.d = (str[i] == 'd') ? 1 : flaguri.d;
			flaguri.m = (str[i] == 'm') ? 1 : flaguri.m;
			flaguri.g_upper = (str[i] == 'G') ? 1 : flaguri.g_upper;
			flaguri.p = (str[i] == 'p') ? 1 : flaguri.p;			
		
		}
		else
		{
			printf("nu-i asa flag\n");
		}
		i++;
	}
}

void	try(char **ac, int len)
{
	int i = 1;
	int ii = 0;
	while (i < len)
	{
		if (!check(ac[i]))
		{
			if (!ii)
				append(&path, ac[i]);
			else
				push(&path, ac[i]);
			ii = 1;
		}
		done(ac[i]);
		i++;
	}
}

int main(int av, char **ac)
{
	(void)av;
	flaguri = *(flag_list*)malloc(sizeof(flag_list) * 1000);
	path = (s_list*)malloc(sizeof(s_list));
	try(ac, av);
	l_flag(ac[1]);
		printf(" flag -l:  %d\n", flaguri.l);
		printf(" flag -R:  %d\n", flaguri.r_upper);
		printf(" flag -a:  %d\n", flaguri.a);
		printf(" flag -r:  %d\n", flaguri.r);
		printf(" flag -t:  %d\n", flaguri.t);
		printf(" flag -u:  %d\n", flaguri.u);
		printf(" flag -f:  %d\n", flaguri.f);
		printf(" flag -g:  %d\n", flaguri.g);	
		printf(" flag -d:  %d\n", flaguri.d);
		printf(" flag -m:  %d\n", flaguri.m);
		printf(" flag -p:  %d\n", flaguri.p);
		printf(" flag -G:  %d\n\n", flaguri.g_upper);
	return (0);
}