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


#include "ft_ls.h"

# define DOHUIA 60000

char filepath[DOHUIA + 1], filename[DOHUIA + 1];
char    *permis(struct stat *elem);
void  recurs(s_list *temp);
s_list	*elemnew(char *name, char *path)
{
	s_list			*elem;
	struct stat		fstat;
	char *store;
	elem = malloc(sizeof(s_list) * sizeof(elem) * 5120 + 1);
	elem->name = ft_strdup(name);
	 // printf("%s\n",elem->name );
	elem->path = ft_strjoin(path, name);
	if (lstat(elem->path, &fstat) == -1)
	{
		return (NULL);
	}
	elem->nlink = fstat.st_nlink;
	elem->uid = fstat.st_uid;
	elem->gid = fstat.st_gid;
	elem->size = fstat.st_size;
	elem->date = fstat.st_ctime;
    elem->timp = ft_strdup(ctime(&elem->date) + 4);
	elem->timp[12] = 0;
	//printf(" huiak huiak %s\n",elem->timp);
    struct passwd *pw = getpwuid(elem->uid);
    elem->pw = pw;
    struct group  *gr = getgrgid(elem->gid);
    elem->gr = gr;
	elem->st_mode = fstat.st_mode;
	elem->blocks = fstat.st_blocks;
	elem->minor = minor(fstat.st_rdev);
	elem->major = major(fstat.st_rdev);
	store = ft_strnew(1);
    store = ft_strjoin(store, permis(&fstat));
    store = ft_strjoin(store, (fstat.st_mode & S_IRUSR) ? "r" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IWUSR) ? "w" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IXUSR) ? "x" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IRGRP) ? "r" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IWGRP) ? "w" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IXGRP) ? "x" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IROTH) ? "r" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IWOTH) ? "w" : "-");
    store = ft_strjoin(store, (fstat.st_mode & S_IXOTH) ? "x" : "-");
    elem->permis = store;
	elem->next = NULL;
	return (elem);
}

void printList(s_list *node)
{
  while (node != NULL)
  {
     printf(" %s \n ", node->name);
     node = node->next;
  }
}
void filtreaza_bazaru_la_lista(s_list **temp)
{
	s_list *cur = *temp, *prev;
		if (cur->name == NULL && cur != NULL)
		{
			*temp = cur->next;
			free(cur);
			return;
		}
		while (cur != NULL && cur->name != NULL)
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur == NULL) return;
		prev->next = cur->next;
		free(cur);
}
void filtreaza_bazaru_la_lista1(s_list **temp)
{
	s_list *cur = *temp, *prev;
		if (cur->name == 0 && cur != NULL)
		{
			*temp = cur->next;
			free(cur);
			return;
		}
		while (cur != NULL && cur->name != 0)
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur == NULL) return;
		prev->next = cur->next;
		free(cur);
}
int		put_the_fuck_in_append(s_list **files, struct dirent *file, char *path)
{
	s_list	*last;

	last = (*files);
	if (!file)
		return (0);
	if (*files == NULL)
	{
		(*files) = elemnew(file->d_name, path);
		return (1);
	}
	while (last->next)
		last = last->next;
	last->next = elemnew(file->d_name, path);
	(*files) = last;
	return (1);
}
int  put_the_fuck_in_push(s_list **headd, struct dirent *d, char *path)
{
	s_list *link = (s_list*)malloc(sizeof(s_list) * 10 + 1);
    struct  stat my_stat;
    char    *store;
    if (!d)
    	return (0);
    //BEGIN put data
    link->name = ft_strdup(d->d_name);
    link->path = ft_strjoin(path, d->d_name);
    link->parent = path;
    lstat(link->path,&my_stat);
    link->size = my_stat.st_size;
    link->date = my_stat.st_ctime;
    link->timp = ft_strdup(ctime(&my_stat.st_ctime) + 4);
	link->timp[12] = 0;
    link->nlink = my_stat.st_nlink;
    link->uid = my_stat.st_uid;
    struct passwd *pw = getpwuid(link->uid);
    link->gid = my_stat.st_gid;
    struct group  *gr = getgrgid(link->gid);
    link->pw = pw;
   	link->st_mode = my_stat.st_mode;
    link->gr = gr;
    link->blocks = my_stat.st_blocks;
 	link->minor = minor(my_stat.st_rdev);
	link->major = major(my_stat.st_rdev);
    store = ft_strnew(1);
    store = ft_strjoin(store, permis(&my_stat));
    store = ft_strjoin(store, (my_stat.st_mode & S_IRUSR) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWUSR) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXUSR) ? "x" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IRGRP) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWGRP) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXGRP) ? "x" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IROTH) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWOTH) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXOTH) ? "x" : "-");
    link->permis = store;
    //END put data
    link->next = (*headd);
    (*headd) = link;
    // free(link);
    return (1);
}
void filtreaza_bazaru_la_path(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	str[i - 1] = (str[i-1] == '.') ? '\0' : str[i-1];
}
void listdir(char *path)
{
	s_list *files = NULL;
	DIR *dir;
	struct dirent *d;
	int i = 0;
	files = (s_list*)malloc(sizeof(s_list) * sizeof(files) * 4096 + 1);
	printf("\n");
	filtreaza_bazaru_la_path(path);
	printf(" %s : \n",path);
	dir = opendir(path);
	char *buf = (char*)malloc(sizeof(char) * 4096 +1);

	if (dir != NULL)
	{

		while ((d = readdir(dir)))
		{		
		  ft_strcpy (buf, path);
		  ft_strcat (buf, "/"); 
			if (i < 2)
			{
			if (flaguri.a)
				put_the_fuck_in_append(&files, d, buf);
			else if (d->d_name[0] != '.')
				put_the_fuck_in_append(&files, d, buf);
			}
			else
			{
				if (flaguri.a)
					put_the_fuck_in_push(&files, d, buf);
				else if (d->d_name[0] != '.')
					put_the_fuck_in_push(&files, d, buf);
			}
			i++;
		}
		closedir(dir);
		filtreaza_bazaru_la_lista(&files);
		MergeSort(&files);
		if (flaguri.r_upper == 1 && g_flagprove == 1)
		{
			printList(files);
		}
		else
		{
			if(flaguri.r == 1)
				reverse(&files);
			if (flaguri.l)
				print_ll(files);
			else
				printList(files);
		}
		recurs(files);
	}
	files = NULL;
	 free(files);
}
void recurs(s_list *temp)
{
	s_list *cur;
	cur = temp;

	while (cur)
	{
		if (cur->name && cur->path && S_ISDIR(cur->st_mode) && ft_strcmp(cur->name, ".") && ft_strcmp(cur->name, ".."))
		{
			listdir(cur->path);
		}
		cur = cur->next;
	}
	free(cur);
}

int ls(char *str)
{
	struct dirent *d;
	DIR *dir;
	s_list *temp = (s_list*)malloc(sizeof(s_list) * 5120);
	char *buf = (char *)malloc(sizeof(char) * 1024);
	g_p = 0;
	if ((dir = opendir(str)) == NULL)
		return (0);
	//buf = ft_strnew(1);
	while ((d = readdir(dir)))
	{
		ft_strcpy (buf, str);
		ft_strcat (buf, "/");
		ft_strcat (buf, d->d_name);
		if (flaguri.a)
			insert(d, buf, str);
		else if (d->d_name[0] != '.')
			insert(d, buf, str);
	}
	filtreaza_bazaru_la_lista1(&head);
	MergeSort(&head);
	if (g_flagprove == 0)
	{
		print_name_by_list(head);
	}
	else
	{
		if (flaguri.r == 1)
		{	
			reverse(&head);
		}
		if (flaguri.l)
		{
			printf("total of %d\n", g_p);
			print_l();
		}
		else
		{
			print_name();
		}
		if (flaguri.r_upper == 1)
		{
			temp = head;
			recurs(temp);
		}
	}
	free(temp);
	closedir(dir);
	return (1);
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
	s_list *link = (s_list*)malloc(sizeof(s_list) * 4096 + 1);
    struct  stat my_stat;
    char    *store;
    link->name = ft_strdup(d->d_name);
    link->path = ft_strjoin(path, str);
    link->parent = str;
    link->next = head;
    lstat(path,&my_stat);
    g_p += (int)my_stat.st_blocks;
    link->size = my_stat.st_size;
    link->date = my_stat.st_ctime;
    link->timp = ft_strdup(ctime(&my_stat.st_ctime) + 4);
	link->timp[12] = 0;
    link->st_mode = my_stat.st_mode;
    link->nlink = my_stat.st_nlink;
    link->uid = my_stat.st_uid;
    struct passwd *pw = getpwuid(link->uid);
    link->gid = my_stat.st_gid;
    struct group  *gr = getgrgid(link->gid);
    link->st_rdev = my_stat.st_rdev;
    link->minor = minor(my_stat.st_rdev);
	link->major = major(my_stat.st_rdev);
	if (link->minor || link->major)
		g_minmaj = 1;
    link->pw = pw;
    link->gr = gr;
    link->blocks = my_stat.st_blocks;
    store = ft_strnew(1);
    store = ft_strjoin(store, permis(&my_stat));
    store = ft_strjoin(store, (my_stat.st_mode & S_IRUSR) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWUSR) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXUSR) ? "x" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IRGRP) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWGRP) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXGRP) ? "x" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IROTH) ? "r" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IWOTH) ? "w" : "-");
    store = ft_strjoin(store, (my_stat.st_mode & S_IXOTH) ? "x" : "-");
    link->permis = store;
    head = link;
}
void    display_file(char *str)
{
    s_list *link = (s_list*) malloc(sizeof(s_list) * 4096);
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
    link->timp = ctime(&my_stat.st_ctime) + 4;
    link->timp[12] = 0;
    if (flaguri.l)
     printf("%s %d %s %s %d %s %s\n",store,(int)my_stat.st_nlink,pw->pw_name,gr->gr_name,(int)my_stat.st_size,
        link->timp,str);
    else printf("%s\n",str);
    free(link);
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
			error(ac[i]);
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
	flaguri = *(flag_list*)malloc(sizeof(flag_list) * 4096 + 2);
	parse(ac, av);

	return (0);
}
