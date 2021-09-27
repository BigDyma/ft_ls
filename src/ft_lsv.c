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
	lungimi lungime;
	temp = headd;
	lungime = antiponturi(temp);
	while (temp)
	{
		if (g_minmaj == 1)
			printf("%s %-*d %-*s %-*s %*d, %*d %-*s %-s\n", temp->permis, lungime.nlink, (int)temp->nlink, lungime.pw_name, temp->pw->pw_name, lungime.gr_name, temp->gr->gr_name, lungime.major, temp->major, lungime.minor, temp->minor, lungime.timp, temp->timp, temp->name);
		else
			printf("%s %-*d %-*s %-*s %*d %-*s %s\n", temp->permis, lungime.nlink, (int)temp->nlink, lungime.pw_name, temp->pw->pw_name, lungime.gr_name, temp->gr->gr_name, lungime.size, (int)temp->size, lungime.timp, temp->timp, temp->name);
		temp = temp->next;
	}
}
lungimi	antiponturi(s_list *headd)
{
	s_list *temp;
	temp = headd;
	lungimi length;
	length.nlink = 0;
	length.pw_name = 0;
	length.gr_name = 0;
	length.size = 0;
	length.timp = 0;
	length.major = 0;
	length.minor = 0;
	while (temp)
	{
		if ((int)ft_strlen(ft_itoa(temp->minor)) > length.minor)
			length.minor = (int)ft_strlen(ft_itoa(temp->minor));
		if ((int)ft_strlen(ft_itoa(temp->major)) > length.major)
			length.major = (int)ft_strlen(ft_itoa(temp->major));
		if ((int)ft_strlen(ft_itoa(temp->nlink)) > length.nlink)
			length.nlink = (int)ft_strlen(ft_itoa(temp->nlink));
		if ((int)ft_strlen(temp->pw->pw_name) > length.pw_name)
			length.pw_name = (int)ft_strlen(temp->pw->pw_name);
		if ((int)ft_strlen(temp->gr->gr_name) > length.gr_name)
			length.gr_name = (int)ft_strlen(temp->gr->gr_name);
		if ((int)ft_strlen(ft_itoa((int)temp->size)) > length.size)
			length.size = (int)ft_strlen(ft_itoa((int)temp->size));
		if ((int)ft_strlen(temp->timp) > length.timp)
			length.timp = (int)ft_strlen(temp->timp);
		temp = temp->next;
	}
	return (length);
}
void baga_timpul_in_lista(s_list **cur)
{
	s_list *temp = *cur;
	while (temp != NULL)
	{
		temp->timp = ctime(&temp->date) + 4;
		temp->timp[12] = 0;
		temp = temp->next;
	}
	*cur = temp;
}

void	print_l()
{
	s_list *temp;
	lungimi lungime;
	temp = head;
	lungime = antiponturi(temp);

	while (temp)
	{
		if (g_minmaj == 1)
			printf("%s  %-*d %-*s  %-*s  %*d, %*d %-*s %-s", temp->permis, lungime.nlink, (int)temp->nlink, lungime.pw_name, temp->pw->pw_name, lungime.gr_name, temp->gr->gr_name, lungime.major, temp->major, lungime.minor, temp->minor, lungime.timp, temp->timp, temp->name);
		else
			printf("%s  %-*d %-*s  %-*s  %*d %-*s %s", temp->permis, lungime.nlink, (int)temp->nlink, lungime.pw_name, temp->pw->pw_name, lungime.gr_name, temp->gr->gr_name, lungime.size, (int)temp->size, lungime.timp, temp->timp, temp->name);
		if (temp->linkof[0] != '\0')
			printf(" -> %s\n",temp->linkof);
		else
			printf("\n");
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
    lstat(str,&my_stat);
    if ((dir = opendir(str)) == NULL)
    {   
        if (errno == 20)
         {   
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
	s_list *a = (s_list*)malloc(sizeof(char) * 1024);
	s_list *b = (s_list*)malloc(sizeof(char) * 1024);
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
	{
		if (a->name != NULL && b->name != NULL)
			c = ft_strcmp(a->name,b->name);
		else
			c = ft_strcmp(a->next->name, b->next->name);
	}
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