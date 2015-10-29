/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:58:09 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/29 02:58:36 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>

t_elem	*create_list(int ac, char **av)
{
	t_elem	*list;
	t_elem	*new;
	t_elem	*prev;
	int		i;

	new = NULL;
	list = (t_elem *)malloc(sizeof(t_elem));
	list->next = list;
	list->prev = list;
	list->name = av[1];
	list->len = ft_strlen(av[1]);
	list->pos_x = 0;
	list->pos_y = 0;
	list->selected = 0;
	list->cursor = 1;
	i = 2;
	prev = list;
	while (i < ac)
	{
		new = (t_elem *)malloc(sizeof(t_elem));
		prev->next = new;
		new->prev = prev;
		new->name = av[i];
		new->len = ft_strlen(av[i]);
		new->pos_x = 0;
		new->pos_y = i - 1;
		new->selected = 0;
		new->cursor = 0;
		prev = new;
		i++;
	}
	if (new)
	{
		new->next = list;
		list->prev = new;
	}
	return (list);
}

void	display_single_list_elem(t_elem *elem)
{
	if (elem->selected)
		tputs(tgetstr("mr", NULL), 1, ft_putchar_ret);
	if (elem->cursor)
		tputs(tgetstr("us", NULL), 1, ft_putchar_ret);
	ft_putstr(elem->name);
	if (elem->selected)
		tputs(tgetstr("me", NULL), 1, ft_putchar_ret);
	if (elem->cursor)
		tputs(tgetstr("ue", NULL), 1, ft_putchar_ret);
}

void	print_arg_list(t_elem *list, int nbr_elem)
{
	t_elem	*tmp;

	tmp = list;
	while (--nbr_elem)
	{
		move_cursor(tmp->pos_x, tmp->pos_y);
		display_single_list_elem(tmp);
		tmp = tmp->next;
	}
}
