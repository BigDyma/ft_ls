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
	elem = malloc(sizeof(s_list) * sizeof(elem) * 10000 + 1);
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
	elem->st_mode = fstat.st_mode;
	elem->blocks = fstat.st_blocks;
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
    lstat(path,&my_stat);
    link->size = my_stat.st_size;
    link->date = my_stat.st_ctime;
    link->nlink = my_stat.st_nlink;
    link->uid = my_stat.st_uid;
    struct passwd *pw = getpwuid(link->uid);
    link->gid = my_stat.st_gid;
    struct group  *gr = getgrgid(link->gid);
    link->pw = pw;
   	link->st_mode = my_stat.st_mode;
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
    //END put data
    link->next = (*headd);
    (*headd) = link;
    return (1);
}
// void	elemgetfiles(s_list **files, char *name, char *path)
// {
// 	s_list *list;
// 	list = *files;
// 	if (list)
// 	{
// 		while (list->next)
// 			list = list->next;
// 		list->next = elemnew(name, path, arg);
// 	}
// 	else
// 		*files = elemnew(name, path, arg);
// }

void suka_ls_dinah(char *str)
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
	files = (s_list*)malloc(sizeof(s_list) * sizeof(files) * 10 + 1);
	printf("\n");
	suka_ls_dinah(path);
	//printf("WTFFFFF\n");
	printf(" %s : \n",path);
	dir = opendir(path);

	if (dir != NULL)
	{
		//printf("inainte de while path\n");
		while ((d = readdir(dir)))
		{		
		// ft_strcpy (buf, str);
		// ft_strcat (buf, "/");
		// ft_strcat (buf, d->d_name);
			if (i < 2)
			{
				//printf("iful 1\n");
			if (flaguri.a)
				put_the_fuck_in_append(&files, d, ft_strjoin(path, "/"));
			else if (d->d_name[0] != '.')
				put_the_fuck_in_append(&files, d, ft_strjoin(path, "/"));
			}
			else
			{
				//printf("iful 2\n");
				if (flaguri.a)
					put_the_fuck_in_push(&files, d, ft_strjoin(path, "/"));
				else if (d->d_name[0] != '.')
					put_the_fuck_in_push(&files, d, ft_strjoin(path, "/"));
			}
			i++;
		}
		closedir(dir);
		MergeSort(&files);
		//printf("??");
			if (flaguri.r_upper == 1)
			{
			//	printf("ahuencik\n");
				printList(files);
				//print_ll(files);
				recurs(files);
				//listdir(head->name);

			}
			//printf("PIZDIK%s\n",files->name);
		files = NULL;
	}
}
void recurs(s_list *temp)
{

	s_list *pizd;
	pizd = temp;

	while (pizd)
	{
		if (pizd->name && pizd->path && S_ISDIR(pizd->st_mode) && ft_strcmp(pizd->name, ".") && ft_strcmp(pizd->name, ".."))
		{
			listdir(pizd->path);
		}
		pizd = pizd->next;
	}
	free(pizd);
}

int ls(char *str)
{
	struct dirent *d;
	DIR *dir;
	s_list *temp = (s_list*)malloc(sizeof(s_list) * 1000);
	char *buf = (char *)malloc(sizeof(char) * 10);
	g_p = 0;
	if ((dir = opendir(str)) == NULL)
		return (0);
	//buf = ft_strnew(1);
	while ((d = readdir(dir)))
	{
		ft_strcpy (buf, str);
		ft_strcat (buf, "/");
		ft_strcat (buf, d->d_name);
		//printf("%s\n",buf);
		//sprintf(buf,"%s/%s",str,d->d_name);
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
			printf("total of %d\n", g_p);
			print_l();
		}
		else
		{
			print_name();
		}
	if (flaguri.r_upper == 1)
	{
		printf("inainte de recursie -- DONE!\n");
		temp = head;
		recurs(temp);
		// listdir(head->name);
	}
	}
	//allfree();
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
	s_list *link = (s_list*)malloc(sizeof(s_list) + 1);
    struct  stat my_stat;
    char    *store;
    link->name = d->d_name;
    link->path = ft_strjoin(path, str);
    link->parent = str;
    link->next = head;
    lstat(path,&my_stat);
    g_p+=(int)my_stat.st_blocks;
    link->size = my_stat.st_size;
    link->date = my_stat.st_ctime;
    link->st_mode = my_stat.st_mode;
    link->nlink = my_stat.st_nlink;
    link->uid = my_stat.st_uid;
    struct passwd *pw = getpwuid(link->uid);
    link->gid = my_stat.st_gid;
    struct group  *gr = getgrgid(link->gid);
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
    s_list *link = (s_list*) malloc(sizeof(s_list));
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
			//printf("o intrat in functie flag(), %s\n",ac[i]);
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
	flaguri = *(flag_list*)malloc(sizeof(flag_list) + 2);
	parse(ac, av);
	//printf("flagul R:%d\n",flaguri.r_upper);
	return (0);
}
