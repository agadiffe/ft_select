/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:58:09 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/09 22:21:13 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>

static t_elem	*list_init_first_elem(char *name)
{
	t_elem	*list;

	list = (t_elem *)malloc(sizeof(t_elem));
	list->next = list;
	list->prev = list;
	list->name = name;
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
	int		i;

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

static void		print_single_list_elem(t_elem *elem)
{
	if (elem->selected)
		tputs(tgetstr("mr", NULL), 1, ft_putchar_ret);
	if (elem->cursor)
		tputs(tgetstr("us", NULL), 1, ft_putchar_ret);
	ft_putstr_fd(elem->name, get_tty(0));
	if (elem->selected)
		tputs(tgetstr("me", NULL), 1, ft_putchar_ret);
	if (elem->cursor)
		tputs(tgetstr("ue", NULL), 1, ft_putchar_ret);
}

void			print_arg_list(t_elem *list)
{
	t_elem	*tmp;
	int		nbr_elem;

	tmp = list;
	nbr_elem = list->prev->pos_list;
	while (nbr_elem--)
	{
		move_cursor(tmp->pos_x, tmp->pos_y);
		print_single_list_elem(tmp);
		tmp = tmp->next;
	}
}
