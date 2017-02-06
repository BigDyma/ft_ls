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
	elem = malloc(sizeof(s_list) * sizeof(elem) * 10 + 1);
	elem->name = ft_strdup(name);	
	printf("%s\n",elem->name );
	elem->path = ft_strjoin(path, name);
	if (lstat(elem->path, &fstat) == -1)
	{
		//basicerror("ft_ls: ", elem->name, 1);
		return (NULL);
	}
	elem->nlink = fstat.st_nlink;
	elem->uid = fstat.st_uid;
	elem->gid = fstat.st_gid;
	elem->size = fstat.st_size;
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
	//elem->date = (arg.u == 1 ? fstat.st_atime : fstat.st_mtime);
	//elem->st_rdev = fstat.st_rdev;
	elem->next = NULL;
	return (elem);
}

int		put_the_fuck_in(s_list **files, struct dirent *file, char *path)
{
	s_list	*list;

	list = *files;
	if (!file)
		return (0);
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elemnew(file->d_name, path);
	}
		*files = list;
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
// int 	 put_the_fuck_in(s_list *temp, struct dirent *d, char *path)
// {
// 	if (temp == NULL)
// 		return (0);
// 	s_list *link = (s_list*)malloc(sizeof(s_list) + 1);
//     struct  stat my_stat;
//     char    *store;
//     link->name = d->d_name;
//     link->path = path;
//     //link->parent = str;
//     link->next = temp;
//     lstat(path,&my_stat);
//     g_p+=(int)my_stat.st_blocks;
//     link->size = my_stat.st_size;
//     link->date = my_stat.st_ctime;
//     link->nlink = my_stat.st_nlink;
//     link->uid = my_stat.st_uid;
//     struct passwd *pw = getpwuid(link->uid);
//     link->gid = my_stat.st_gid;
//     struct group  *gr = getgrgid(link->gid);
//     link->pw = pw;
//     link->gr = gr;
//     link->blocks = my_stat.st_blocks;
//     store = ft_strnew(1);
//     store = ft_strjoin(store, permis(&my_stat));
//     store = ft_strjoin(store, (my_stat.st_mode & S_IRUSR) ? "r" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IWUSR) ? "w" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IXUSR) ? "x" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IRGRP) ? "r" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IWGRP) ? "w" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IXGRP) ? "x" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IROTH) ? "r" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IWOTH) ? "w" : "-");
//     store = ft_strjoin(store, (my_stat.st_mode & S_IXOTH) ? "x" : "-");
//     link->permis = store;
// //     temp = link;
//     return (1);
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
	files = (s_list*)malloc(sizeof(s_list) * sizeof(files) * 10 + 1);
	//char *buf = (char *)malloc(sizeof(char) * 10);
	printf("\n");
	//printf("list dir -- DONE\n");
	suka_ls_dinah(path);
		printf(" %s : \n",path);
	dir = opendir(path);
	if (dir != NULL)
	{
		printf("inainte de while path\n");
		//while (put_the_fuck_in(&files, readdir(dir), ft_strjoin(path, "/")) != 0)
		//	;
		while ((d = readdir(dir)))
		{		
		//	printf("huuuiiaaak\n");
			if (flaguri.a)
				put_the_fuck_in(&files, d, ft_strjoin(path, "/"));
			else if (d->d_name[0] != '.')
				put_the_fuck_in(&files, d, ft_strjoin(path, "/"));
		}
					closedir(dir);
		MergeSort(&files);
		if (g_flagprove == 0)
		{
			print_name();
		}
		else
		{
			if (flaguri.r == 1)
			{	
				reverse(&files);
			}
		if (flaguri.r_upper == 1)
		{
			printf("ahuencik\n");
			print_name_by_list(files);
			recurs(files);
			//listdir(head->name);
		}
			//printf("PIZDIK%s\n",files->name);
		// files = NULL;
	return;
	}
	//else
	//{
	//	error(path);
	//}
	}
	else
	{
		printf("URA\n");
		return;
	}
}
void recurs(s_list *temp)
{

	s_list *pizd;
	pizd = temp;

	while (pizd)
	{
				printf("AQAAAAAAAAAAAAA %s \n", pizd->path);
		if (pizd->permis[0] == 'd' && ft_strcmp(pizd->name, ".") && ft_strcmp(pizd->name, ".."))
		{
			printf("New path\n");
			// pizd->path = ft_strjoin(pizd->path, "/");
			// pizd->path = ft_strjoin(pizd->path, pizd->name);
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
