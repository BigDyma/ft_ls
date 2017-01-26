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

void listdir(char *dir)
{
	printf(" HUIAK \n\n %s :\n",dir);
    DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
   
    if((dp = opendir(dir)) == NULL) 
    {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) 
    {
        if(lstat(entry->d_name, &statbuf) == 0)
        {
            if(statbuf.st_mode & S_IFDIR)
            {
                /* Found a directory, but ignore . and .. */
                if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                    continue;

             int len = strlen(filepath);
			strcat(filepath, entry->d_name);
			strcat(filepath, "/");

		/* Recurse at a new indent level */
			listdir(entry->d_name);

		/* cleanup filepath */
			filepath[len] = '\0';
                listdir(entry->d_name);
               
            }
            else
            {
                // Concatenate file name
                strcpy(filename, filepath);
                strcat(filename, entry->d_name);
                //puts(filename);
               // error(entry->d_name);
                printf("%s\n",entry->d_name);
               
            }
        }
    }
    chdir("..");
    closedir(dp);
}
void recurs()
{
	s_list *temp = (s_list*)malloc(sizeof(s_list) * 2);
	temp = head;
	while (temp)
	{
		if (temp->permis[0] == 'd')
			listdir(temp->name);

		temp = temp->next;
	}
}

int ls(char *str)
{
	struct dirent *d;
	DIR *dir;
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
		printf("Huiak \n");
		recurs();
		listdir(".");
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
    link->path = path;
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


    
    #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  char nume[200];
  char familie[200];
} node;

int valid(char c)
{
   return (c >= 'a' && c <= 'z' || c <= 'Z' && c >= 'A' || c <= '9' && c >= '0');
}

void searchName(node *data, int col)
{
    node temp;
    int i = 0;
    int j = 0;
   for (i = 0; i < col - 1; i++)
        for (j = i + 1; j < col; j++)
        {
            printf("\n|%d %d|->%s<- ->%s<-",i, j, data[i].nume, data[j].nume);
            if (strcmp(data[i].nume, data[j].nume) == 0)
            {
               // ft_swap(&data[i].nume, &data[i].familie);
                char aux[200];
                strcpy(aux , data[i].nume);
                strcpy(data[i].nume ,data[i].familie);
                strcpy(data[i].familie , aux);
                printf("\n-------------------------\n%s \t %s", data[i].nume, data[i].familie);
                break;
            }
        }
}
int main()
 {
    char line[1024];
    node data[70];
    node temp;
    int i = 0;
    int col = 0;
    int fam = 0;
    int num = 0;
    freopen("file.txt","r", stdin);
    int space = 0;
    while( fgets(line,1024,stdin) )
    {
        fam = 0;
        num = 0;
        i = 0;
        space = 0;
            while (line[i])
            {
                 if (line[i] <= 32)
                 {
                   space = 1;
                 }
                if (space == 0)
                {
                    data[col].familie[fam] = line[i];
                    fam++;
                }
                else if (space == 1 && valid(line[i]))
                {
                    data[col].nume[num] = line[i];
                    num++;
                }
                i++;
            }
        data[col].familie[fam] = '\0';
        data[col].nume[num] = '\0';
        col++;
    }
    int j = 0;

    searchName(data, col);
    for (i = 0; i < col; i++)
    {
        for ( j = i + 1; j < col; j++)
        {
            if (strcmp(data[i].familie, data[j].familie) > 0)
            {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    i = 0;
    printf("is Daun\n");
     for (i = 0; i < col; i++)
         printf("\nfamilie:%s \tnume:%s\n", data[i].familie, data[i].nume);
    return 0;
}