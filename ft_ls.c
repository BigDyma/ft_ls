/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstrelet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:56:38 by dstrelet          #+#    #+#             */
/*   Updated: 2017/01/11 16:42:53 by dstrelet         ###   ########.fr       */
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
s_list	*head = NULL;
int g_p;
int g_flagprove;
s_list *SortedMerge(s_list *a, s_list *b);
s_list *SortedMerget(s_list *a, s_list *b);
void FrontBackSplit(s_list *source,
		s_list **frontRef, s_list **backRef);

void MergeSort(s_list **headRef)
{
	s_list *headd = *headRef;
	s_list *a;
	s_list *b;

	if ((headd == NULL) || (headd->next == NULL))
	{
		return;
	}

	FrontBackSplit(headd, &a, &b); 

	MergeSort(&a);
	MergeSort(&b);

	// *headRef = SortedMerget(a,b);
	*headRef = SortedMerge(a, b);

}

s_list *SortedMerge(s_list *a, s_list *b)
{
	s_list *result = NULL;

	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);
	int c;
	if (flaguri.t == 1)
		c = difftime(b->date, a->date);
	else
		c = ft_strcmp(a->name,b->name);
	if (c <= 0)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}


void FrontBackSplit(s_list *source,
		s_list **frontRef, s_list **backRef)
{
	s_list *fast;
	s_list *slow;
	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}
void recurs()
{
	DIR 	*dir;
	s_list *temp = (s_list*)malloc(sizeof(s_list) * 10 + 1);
	temp = head;
	while (temp != NULL)
	{
		if (temp->permis[0] == 'd')
		{
			//intra in fisier
			temp->parent = ft_strjoin(temp->parent,"/");
            temp->name = ft_strjoin(temp->parent,temp->name);
            if ((dir = opendir(temp->name)) != NULL)
                printf(" %s :\n",temp->name);
            printf("\n\n");
		}
		temp = temp->next;
	}
}
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
	return(ft_strlen(str) == 2 && str[0] == '-' && 
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
			g_flagprove++;
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
		printf("%s\n",temp->name);
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

void    display_file(char *str)
{
    s_elem *link = (t_elem*) malloc(sizeof(t_elem));
    struct  stat my_stat;
    char    *store;
    lstat(str,&my_stat);
    struct passwd *pw = getpwuid(my_stat.st_uid);
    struct group  *gr = getgrgid(my_stat.st_gid);
    store = ft_strnew(1);
    if (S_ISLNK(my_stat.st_mode))
        store = ft_strjoin(store,"l");
    else
        store = ft_strjoin(store,(S_ISDIR(my_stat.st_mode)) ? "d" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IRUSR) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWUSR) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXUSR) ? "x" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IRGRP) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWGRP) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXGRP) ? "x" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IROTH) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWOTH) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXOTH) ? "x" : "-");
    link->time = ctime(&my_stat.st_ctime) + 4;
    link->datee[12] = 0;
    if (flags.l)
    printf("%s %d %s %s %d %s %s\n",store,(int)my_stat.st_nlink,pw->pw_name,gr->gr_name,(int)my_stat.st_size,
        link->datee,str);
    else printf("%s\n",str);
}

void    error(char *str)
{
    DIR *dir;
    struct  stat my_stat;

    lstat(str,&my_stat);
    if ((dir = opendir(str)) == NULL)
    {   
        if (errno == 20)
         {   
            //printf("%s\n",str);
            display_file(str);
            return ;
         }
        char *stru;
        stru = ft_strnew(1);
        stru = ft_strjoin(stru,"ft_ls: cannot open directory ");
       stru = ft_strjoin(stru,str);
        perror(stru);
    }
    if (S_ISLNK(my_stat.st_mode))
    {    
        display_file(str);
        return ;
    }
    ls(str);
}

static void reverse(s_list **head_ref)
{
	s_list *prev   = NULL;
	s_list *current = *head_ref;
	s_list *next;
	while (current != NULL)
	{
		next  = current->next;  
		current->next = prev;   
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

int ls(char *str)
{
	struct dirent *d;
	DIR *dir;
	char *buf = (char *)malloc(sizeof(char) * sizeof(buf) *  2048);
	if ((dir = opendir(str)) == NULL)
		return (0);
	//buf = ft_strnew(1);
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
	MergeSort(&head);
	if (g_flagprove == 0)
	{
		print_name();
	}
	else
	{
		if (flaguri.r == 1)
		{	
			reverse(&head);
		}
		if (flaguri.l)
		{
			print_l();
		}
		else
		{
			print_name();
		}
	}
	if (flaguri.r_upper == 1)
	{
			recurs();
	}

	//allfree();
	closedir(dir);
	return (1);
}

void	parse(char **ac, int len)
{
	int i = 1;
	int filefound = 0;
	int firstmin = 0;
	while (i < len)
	{
		//Daca ac[i] nu ii flag atunci el il cauta 
		// ca fisier 
		if (minmin(ac[i]) && firstmin == 0 && filefound == 0)
		{
			firstmin = 1;
			filefound = 1;
			i++; 
			continue;
		}
		else if (!flag(ac[i]) || filefound == 1)
		{
			printf("o intrat in functie flag(), %s\n",ac[i]);
				ls(ac[i]);
			filefound = 1;
		}
		else if (filefound == 0)
			searchflag(ac[i]);
		i++;
	}
	if (filefound == 0)
	{
		ls(".");
	}
}

int main(int av, char **ac)
{
	flaguri = *(flag_list*)malloc(sizeof(flag_list) + 2);
	parse(ac, av);
	//printf("flagul R:%d\n",flaguri.r_upper);
	return (0);
}
