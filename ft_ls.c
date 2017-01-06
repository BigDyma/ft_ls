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
		
		}
		else
		{
			printf("nu-i asa flag\n");
		}
		i++;
	}
}

int ls(char *str)
{
	struct dirent *d;
	DIR *dir;
}

void	parse(char **ac, int len)
{
	int i = 1;
	int ii = 0;
	while (i < len)
	{
		if (!check(ac[i]) || ii == 1)
		{
			ls(ac[i]);
			ii = 1;
		}
		if (!ii)
			searchflag(ac[i]);
		i++;
	}
}

int main(int av, char **ac)
{
	(void)av;
	flaguri = *(flag_list*)malloc(sizeof(flag_list));
	parse(ac, av);
	return (0);
}