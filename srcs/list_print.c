/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:57:39 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/29 20:02:36 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"

static void		print_single_list_elem(t_elem *elem)
{
	if (elem->selected)
		tputs(tgetstr("mr", NULL), 1, ft_putchar_ret);
	if (elem->cursor)
	{
		ft_putstr_fd("\033[31;1m", get_tty(0));
		tputs(tgetstr("us", NULL), 1, ft_putchar_ret);
	}
	else if (elem->color)
		ft_putstr_fd(elem->color, get_tty(0));
	ft_putstr_fd(elem->name, get_tty(0));
	if (elem->selected)
		tputs(tgetstr("me", NULL), 1, ft_putchar_ret);
	if (elem->cursor)
	{
		ft_putstr_fd("\033[0m", get_tty(0));
		tputs(tgetstr("ue", NULL), 1, ft_putchar_ret);
	}
	else if (elem->color)
		ft_putstr_fd("\033[0m", get_tty(0));
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
