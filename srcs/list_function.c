/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 03:39:56 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/26 03:49:36 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_elem		*get_current_elem(t_elem *list)
{
	t_elem	*tmp;

	tmp = list;
	while (tmp->cursor != 1)
		tmp = tmp->next;
	return (tmp);
}

int			get_nbr_elem_per_col(t_elem *list)
{
	t_elem	*tmp;
	int		nbr_elem_col;

	nbr_elem_col = 1;
	tmp = list->next;
	while (tmp->col_n == tmp->next->col_n && tmp->pos_list != 1)
	{
		tmp = tmp->next;
		nbr_elem_col++;
	}
	return (nbr_elem_col);
}

void		list_update_pos(t_elem *list, int elem_del)
{
	t_elem	*tmp;
	int		nbr_elem;

	nbr_elem = list->prev->pos_list;
	tmp = get_current_elem(list);
	while (elem_del < nbr_elem)
	{
		tmp->pos_list -= 1;
		if (tmp->pos_y == 0 && tmp->pos_x != 0)
		{
			tmp->pos_x = tmp->prev->pos_x;
			tmp->pos_y = tmp->prev->pos_y + 1;
			tmp->col_n -= 1;
		}
		else
			tmp->pos_y -= 1;
		tmp = tmp->next;
		elem_del++;
	}
}

int			list_get_max_len(t_elem *list)
{
	int		max_len;
	t_elem	*tmp;

	max_len = list->len;
	tmp = list->next;
	while (tmp->pos_list != 1)
	{
		if (max_len < tmp->len)
			max_len = tmp->len;
		tmp = tmp->next;
	}
	return (max_len);
}
