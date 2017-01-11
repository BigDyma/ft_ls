#include "ls.h"

int g_p;
int g_t;
int g_n;
t_elem *head = NULL;
t_elem *current = NULL;
t_flag  flags;

t_elem *SortedMerge(t_elem *a, t_elem *b);
t_elem *SortedMerget(t_elem *a, t_elem *b);
void FrontBackSplit(t_elem *source,
          t_elem **frontRef, t_elem **backRef);

void MergeSort(t_elem **headRef)
{
  t_elem *headd = *headRef;
  t_elem *a;
  t_elem *b;

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

t_elem *SortedMerge(t_elem *a, t_elem *b)
{
  t_elem *result = NULL;

  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
  int c;
  if (flags.t == 1)
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


void FrontBackSplit(t_elem *source,
          t_elem **frontRef, t_elem **backRef)
{
  t_elem *fast;
  t_elem *slow;
  if (source==NULL || source->next==NULL)
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

void display()
{
    t_elem *temp;
    temp = head;
    while (temp!=NULL)
    {
        printf("%s",temp->permis);
        printf(" %d",(int)temp->nlink);
        temp->datee = ctime(&temp->date) + 4;
        temp->datee[12] = 0;
        printf(" %s %s %5d %s %s\n",temp->pw->pw_name,temp->gr->gr_name,(int)temp->size, temp->datee, temp->name);
        temp=temp->next;
    }
}

void displayl()
{
    t_elem *temp;
    temp = head;
    while (temp!=NULL)
    {
        printf("%s ",temp->name);
        temp=temp->next;
    }
    printf("\n");
}

static void reverse(t_elem **head_ref)
{
    t_elem *prev   = NULL;
    t_elem *current = *head_ref;
    t_elem *next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void    recurs()
{
    DIR *dir;
    t_elem *temp;
    temp = head;
    while (temp!=NULL)
    {
        if (temp->permis[0] == 'd')
        {

            temp->parent = ft_strjoin(temp->parent,"/");
            temp->name = ft_strjoin(temp->parent,temp->name);
            if ((dir = opendir(temp->name)) != NULL)
                printf(" %s :\n",temp->name);
            error(temp->name);
            printf("\n\n");
            g_n++;
        }
        temp=temp->next;
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

void insertFirst(struct dirent *d, char *path, char *str)
{
    t_elem *link = (t_elem*) malloc(sizeof(t_elem));
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

int ls(char *str)
{
    struct dirent   *d;
    DIR *dir;
    char buf[512];
    g_p = 0;
    head = NULL;
    if (!str)
        str = ".";
    if ((dir = opendir(str)) == NULL)
        return (0);
    while ((d = readdir(dir)))
    {
         ft_strcpy (buf, str);
        ft_strcat (buf, "/");
        ft_strcpy (buf, d->d_name);
      // sprintf(buf,"%s/%s",str,d->d_name);
        if (flags.a)
            insertFirst(d,buf,str);
        else if (d->d_name[0] != '.')
            insertFirst(d,buf,str);
    }
    MergeSort(&head);
    if (g_t > 1)
        printf("%s:\n",str);
    if (flags.r == 1)
        reverse(&head);
    if (flags.l == 1)
    {
        printf("total of %d\n",g_p/2);
        display();
    }
    else
        displayl();
     if (flags.R == 1)
        recurs();
    closedir(dir);
    return (1);
}

void    display_file(char *str)
{
    t_elem *link = (t_elem*) malloc(sizeof(t_elem));
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
    link->datee = ctime(&my_stat.st_ctime) + 4;
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

void    parse(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 'l')
            flags.l = 1;
        if (str[i] == 'a')
            flags.a = 1;
        if (str[i] == 'r')
            flags.r = 1;
        if (str[i] == 'R')
            flags.R = 1;
        if (str[i] == 't')
            flags.t = 1;
        i++;
    }
}

int main(int argc, char **argv)
{
    int i;

    g_t = 0;
    if (argc)
    {
        for (i=1;i<argc;i++)
            if (argv[i][0] == '-' && argv[i][1] != '\0')
                parse(argv[i]);
            else
                g_t++;
        for (i=1;i<argc;i++)
        {
            if (argv[i][0] != '-')
                error(argv[i]);
            if (argv[i][0] == '-' && argv[i][1] == '\0')
                error("-");
        }
    }
    if (g_t == 0)
        ls(".");
    return (0);
}
