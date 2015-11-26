/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 03:34:43 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/26 03:51:17 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		handle_down_and_up(t_elem *list, int up_key)
{
	t_elem	*tmp;

	tmp = get_current_elem(list);
	tmp->cursor = 0;
	if (up_key)
		tmp->prev->cursor = 1;
	else
		tmp->next->cursor = 1;
}

static void		handle_right(t_elem *list, t_elem *tmp, int nbr_elem_col)
{
	int		nbr_col;
	int		current_pos_elem;

	nbr_col = list->prev->col_n;
	if ((nbr_col == 0 && tmp->pos_y == nbr_elem_col - 1)
			|| (tmp->col_n == nbr_col - 1 && tmp->pos_y > list->prev->pos_y
				&& tmp->col_n != tmp->next->col_n)
			|| (tmp->pos_list == list->prev->pos_list
				&& tmp->pos_y == nbr_elem_col))
		list->cursor = 1;
	else
	{
		current_pos_elem = tmp->pos_y;
		if ((tmp->col_n == nbr_col - 1 && tmp->pos_y > list->prev->pos_y)
				|| tmp->col_n == nbr_col)
		{
			tmp = tmp->next;
			current_pos_elem++;
		}
		tmp = tmp->next;
		while (tmp->pos_y != current_pos_elem)
			tmp = tmp->next;
		tmp->cursor = 1;
	}
}

static void		handle_left(t_elem *list, t_elem *tmp, int nbr_elem_col)
{
	int		nbr_col;
	int		current_pos_elem;

	nbr_col = list->prev->col_n;
	if (tmp->pos_list == 1 && (nbr_elem_col == list->prev->pos_y || !nbr_col))
		list->prev->cursor = 1;
	else if (tmp->pos_list == 1)
	{
		while (tmp->pos_y != nbr_elem_col)
			tmp = tmp->prev;
		tmp->cursor = 1;
	}
	else
	{
		current_pos_elem = tmp->pos_y;
		if (tmp->col_n == 0)
		{
			tmp = tmp->prev;
			current_pos_elem--;
		}
		tmp = tmp->prev;
		while (tmp->pos_y != current_pos_elem)
			tmp = tmp->prev;
		tmp->cursor = 1;
	}
}

static void		handle_right_and_left(t_elem *list, int right)
{
	t_elem	*tmp;
	int		nbr_elem_col;

	nbr_elem_col = get_nbr_elem_per_col(list);
	tmp = get_current_elem(list);
	tmp->cursor = 0;
	if (right)
		handle_right(list, tmp, nbr_elem_col);
	else
		handle_left(list, tmp, nbr_elem_col);
}

void			handle_arrow(t_elem *list, int key)
{
	if (key == UP_KEY)
		handle_down_and_up(list, 1);
	else if (key == DOWN_KEY)
		handle_down_and_up(list, 0);
	else if (key == RIGHT_KEY)
		handle_right_and_left(list, 1);
	else
		handle_right_and_left(list, 0);
}
