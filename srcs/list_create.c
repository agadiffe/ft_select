/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:58:09 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/29 20:02:56 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <sys/stat.h>

static char		*get_color(const char *arg)
{
	struct stat		stat;

	if (lstat(arg, &stat) == -1)
		return (NULL);
	else if (S_ISLNK(stat.st_mode))
		return ("\033[36;1m");
	else if (S_ISDIR(stat.st_mode))
		return ("\033[34;1m");
	else if (S_ISBLK(stat.st_mode))
		return ("\033[33;1m");
	else if (S_ISCHR(stat.st_mode))
		return ("\033[33;1m");
	else if (S_ISSOCK(stat.st_mode))
		return ("\033[35;1m");
	else if (S_ISFIFO(stat.st_mode))
		return ("\033[33;1m");
	else if (stat.st_mode & S_IXUSR)
		return ("\033[32;1m");
	else if (!(stat.st_mode & S_IRUSR))
		return ("\033[37;1m");
	else
		return (NULL);
}

static t_elem	*list_init_first_elem(char *name)
{
	t_elem	*list;

	list = (t_elem *)malloc(sizeof(t_elem));
	list->next = list;
	list->prev = list;
	list->name = name;
	list->color = get_color(name);
	list->len = ft_strlen(name);
	list->pos_x = 0;
	list->pos_y = 0;
	list->selected = 0;
	list->cursor = 1;
	list->pos_list = 1;
	list->col_n = 0;
	return (list);
}

static void		list_push_back_elem(t_elem **list, char *name, int pos_list)
{
	t_elem	*tmp;
	t_elem	*new;

	tmp = *list;
	while (tmp->pos_list != pos_list - 1)
		tmp = tmp->next;
	new = (t_elem *)malloc(sizeof(t_elem));
	new->next = (*list);
	new->prev = tmp;
	new->name = name;
	new->color = get_color(name);
	new->len = ft_strlen(name);
	new->pos_x = 0;
	new->pos_y = pos_list - 1;
	new->selected = 0;
	new->cursor = 0;
	new->pos_list = pos_list;
	new->col_n = 0;
	(*list)->prev = new;
	tmp->next = new;
}

t_elem			*get_list(int ac, char **av)
{
	static t_elem	*list;
	int				i;

	if (!list)
	{
		list = list_init_first_elem(av[1]);
		i = 2;
		while (i < ac)
		{
			list_push_back_elem(&list, av[i], i);
			i++;
		}
	}
	return (list);
}
