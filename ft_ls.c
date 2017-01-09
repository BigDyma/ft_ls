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
#include "ft_ls.h"

flag_list flaguri;
s_list	*head;
int g_p;
int g_check;

int		flag(char *str)
{
	int i = 0;
	size_t min = 0;
	//printf("functia flag, string:%s\n", str);
	while (str[i])
	{
		if (str[i] == '-')
			min++;
		i++;
	}
	return ((str[0] == '-' && str[1]) && min == 1);
}
int minmin(char *str)
{
	return(ft_strlen(str) == 1 && str[0] == '-' && 
   		   str[1] == '-' && str[2] == '\0');
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

void searchflag(char *str)
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
			g_check++;
		}
		else
			printf("nu-i asa flag\n");
		i++;
	}
}

void print_name()
{
	s_list *temp;
	temp = head;
	while (temp != NULL)
	{
		printf("%s\t",temp->name);
		temp=temp->next;
	}
}
void	print_l()
{
	s_list *temp;
	temp = head;
	while (temp != NULL)
	{
		printf("%s",temp->permis);
		printf(" %d",(int)temp->nlink);
		temp->timp = ctime(&temp->date) + 4;
		temp->timp[12] = 0;
		printf(" %s %s %5d %s %s\n",temp->pw->pw_name,temp->gr->gr_name,(int)temp->size, temp->timp, temp->name);
        temp = temp->next;
	}
}
void sortbytime()
{
	
}
void sort(d_lst *node)
{
	if (flaguri.t)
	{
		sortbytime()
	}
}
char    *permis(struct stat *elem)
{
    if(S_ISFIFO(elem->st_mode))
        return("p") ;
    if((S_ISCHR(elem->st_mode)))
        return ("c");
    if((S_ISDIR(elem->st_mode)))
    return ("d");
    if (S_ISBLK(elem->st_mode))
        return ("b");
    if (S_ISREG(elem->st_mode))
        return ("-");
    if (S_ISLNK(elem->st_mode))
        return ("l");
    if (S_ISSOCK(elem->st_mode))
        return ("s");
    return ("-");
}
void insert(struct dirent *d, char *path, char *str)
{
	s_list *link = (s_list*)malloc(sizeof(s_list) + 1);
	struct stat st;
	char *store;
	link->name = d->d_name;
    link->path = path;
    link->parent = str;
    link->next = head;
    lstat(path,&st);
    g_p +=(int)st.st_blocks;
    link->size = st.st_size;
    link->date = st.st_ctime;
    link->nlink = st.st_nlink;
    link->uid = st.st_uid;
    struct passwd *pw = getpwuid(link->uid);
    link->gid = st.st_gid;
    struct group  *gr = getgrgid(link->gid);
    link->pw = pw;
    link->gr = gr;
    link->blocks = st.st_blocks;
    store = ft_strnew(1);
    store = ft_strjoin(store, permis(&st));
    store = ft_strjoin(store, (st.st_mode & S_IRUSR) ? "r" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IWUSR) ? "w" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IXUSR) ? "x" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IRGRP) ? "r" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IWGRP) ? "w" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IXGRP) ? "x" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IROTH) ? "r" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IWOTH) ? "w" : "-");
    store = ft_strjoin(store, (st.st_mode & S_IXOTH) ? "x" : "-");
    link->permis = store;
    head = link;
}
int ls(char *str)
{
	struct dirent *d;
	DIR *dir;
	char *buf = (char *)malloc(sizeof(char) * sizeof(buf) + 1);
	if ((dir = opendir(str)) == NULL)
		return (0);
	while ((d = readdir(dir)))
	{
		ft_strcpy (buf, str);
        ft_strcat (buf, "/");
        ft_strcpy (buf, d->d_name);
        if (flaguri.a)
        	insert(d, buf, str);
        else if (d->d_name[0] != '.')
        	insert(d, buf, str);
	}
	//sort(&head);
	if (g_check == 0)
		print_name();
	// if (flaguri.r)
	//		reverse(&head);
	 if (flaguri.l)
	 	print_l();
	//if (flaguri.R)
	//		recurs();

	//allfree();
	//closedir(dir);
	return (1);
}

void	parse(char **ac, int len)
{
	int i = 1;
	int ii = 0;
	int check = 0;
	while (i < len)
	{
		//Daca ac[i] nu ii flag atunci el il cauta 
		// ca fisier 
		//printf("valoarea functiei flag(): %d\n", flag(ac[i]));
		if (check == 1)
			{
			ls(ac[i]);
			i++; 
			continue ;
			}
		if (!flag(ac[i])|| ii == 1 || (check == 0 && ii == 0))
		{
		//	printf("o intrat in functie flag()\n" );
			if (minmin(ac[i]))
			{
				check = 1;
				i++;
			}
			ls(ac[i])
			ii = 1;
		}
		if (ii == 0)
			searchflag(ac[i]);
		i++;
	}
}

int main(int av, char **ac)
{
	flaguri = *(flag_list*)malloc(sizeof(flag_list) + 1);
	if (av == 1)
	{
		ls(".");
	}
	parse(ac, av);
	//printf("flagul l:%d\n",flaguri.l);
	return (0);
}
