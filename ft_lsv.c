#include "ft_ls.h"

void 	print_name_by_list(s_list *temp)
{
	s_list *current;
	current = temp;
	while (current != NULL)
	{
		printf("%s\n",current->name);
		current=current->next;
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
void	print_ll(s_list *headd)
{
	s_list *temp;
	temp = headd;
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
void fuckof(char str)
{
	printf("ls: illegal option  -- %c\n\nusage: ls [-lRarGtufgdmp] [file ...]\n", str);
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
		{
			fuckof(str[i]);
			exit(1);
		}
		i++;
	}
}

void    error(char *str)
{
    DIR *dir;
    struct  stat my_stat;
   // printf("o intrat in error()\n");
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
void reverse(s_list **head_ref)
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

// int		get_max_major_len(s_list *begin)
// {
// 	int		max;
// 	s_file	*file;
// 	t_list	*l;

// 	if (begin == NULL)
// 		return (0);
// 	max = 0;
// 	l = begin;
// 	while (l)
// 	{
// 		file = (s_file*)l->content;
// 		if (file != NULL && ft_nbrlen_signed(file->major, 10) > max)
// 			max = ft_nbrlen_signed(file->major, 10);
// 		l = l->next;
// 	}
// 	return (max);
// }
// static int	get_max_hard_links_len(t_list *begin)
// {
// 	int		max;
// 	t_file	*file;
// 	t_list	*l;

// 	if (begin == NULL)
// 		return (0);
// 	max = 0;
// 	l = begin;
// 	while (l)
// 	{
// 		file = (t_file*)l->content;
// 		if (file != NULL && ft_nbrlen_signed(file->hard_links, 10) > max)
// 			max = ft_nbrlen_signed(file->hard_links, 10);
// 		l = l->next;
// 	}
// 	return (max);
// }

// static int	get_max_size_len(t_list *begin)
// {
// 	int		max;
// 	t_file	*file;
// 	t_list	*l;

// 	if (begin == NULL)
// 		return (0);
// 	max = 0;
// 	l = begin;
// 	while (l)
// 	{
// 		file = (t_file*)l->content;
// 		if (file != NULL && ft_nbrlen_signed((long long)file->size, 10) > max)
// 			max = ft_nbrlen_signed((long long)file->size, 10);
// 		l = l->next;
// 	}
// 	return (max);
// }

// static int	get_max_owner_len(t_list *begin)
// {
// 	int		max;
// 	t_file	*file;
// 	t_list	*l;

// 	if (begin == NULL)
// 		return (0);
// 	max = 0;
// 	l = begin;
// 	while (l)
// 	{
// 		file = (t_file*)l->content;
// 		if (file != NULL && ft_strlen(file->owner) > max)
// 			max = (int)ft_strlen(file->owner);
// 		l = l->next;
// 	}
// 	return (max);
// }

// static int	get_max_group_len(t_list *begin)
// {
// 	int		max;
// 	t_file	*file;
// 	t_list	*l;

// 	if (begin == NULL)
// 		return (0);
// 	max = 0;
// 	l = begin;
// 	while (l)
// 	{
// 		file = (t_file*)l->content;
// 		if (file != NULL && ft_strlen(file->group) > max)
// 			max = (int)ft_strlen(file->group);
// 		l = l->next;
// 	}
// 	return (max);
// }

// void		set_max(t_list *files, t_max *max)
// {
// 	max->max_hard_links_len = get_max_hard_links_len(files);
// 	max->max_size_len = get_max_size_len(files);
// 	max->max_owner_len = get_max_owner_len(files);
// 	max->max_group_len = get_max_group_len(files);
// 	max->max_major = get_max_major_len(files);
// 	max->max_minor = get_max_minor_len(files);
// }
// int		get_max_minor_len(s_list *begin)
// {
// 	int		max;
// 	t_file	*file;
// 	t_list	*l;

// 	if (begin == NULL)
// 		return (0);
// 	max = 0;
// 	l = begin;
// 	while (l)
// 	{
// 		file = (t_file*)l->content;
// 		if (file != NULL && ft_nbrlen_signed(file->minor, 10) > max)
// 			max = ft_nbrlen_signed(file->minor, 10);
// 		l = l->next;
// 	}
// 	return (max);
// }

// void recurs(char *str)
// {
// 	DIR 	*dir;
// 	s_list *temp = (s_list*)malloc(sizeof(s_list) * 10 + 1);
// 	temp = head;
// 	char *buf = (char *)malloc(sizeof(char) * sizeof(buf) *  2048);
// 	int rwb = 0;
// 	while (d = readdir(dir))
// 	{	
// 		ft_strcpy (buf, str);
// 		ft_strcat (buf, "/");
// 		ft_strcat (buf, d->d_name);

// 	}
// 	struct dirent *d;
// 	while (temp != NULL)
// 	{
// 		if (temp->permis[0] == 'd')
// 		{
// 			//intra in fisier
// 			temp->parent = ft_strjoin(temp->parent,"/");
//             temp->name = ft_strjoin(temp->parent,temp->name);
//             if ((dir = opendir(temp->name)) != NULL)
//                 printf(" %s :\n",temp->name);
//             error(temp->name);
//             printf("\n\n");
// 		}
// 		temp = temp->next;
// 	}
// }

