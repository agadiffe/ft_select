/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 03:47:55 by agadiffe          #+#    #+#             */
/*   Updated: 2016/01/10 20:00:34 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"

int				*get_enought_space(void)
{
	static int		enought_space;

	return (&enought_space);
}

static void		list_update(t_elem *list, int row_term,
							int nbr_elem, int max_len)
{
	t_elem	*tmp;
	int		i;
	int		col;

	col = 0;
	tmp = list;
	while (nbr_elem)
	{
		i = 0;
		while (i < row_term && nbr_elem)
		{
			tmp->col_n = col;
			tmp->pos_x = col * (max_len + 2);
			tmp->pos_y = i;
			tmp = tmp->next;
			i++;
			nbr_elem--;
		}
		col++;
	}
}

int				check_window_size(t_elem *list)
{
	t_win	ws;
	int		nbr_elem;
	int		nbr_col;
	int		max_len;

	ws = get_window_size();
	nbr_elem = list->prev->pos_list;
	max_len = list_get_max_len(list);
	list_update(list, ws.row_term, nbr_elem, max_len);
	nbr_col = list->prev->col_n;
	if (ws.col_term >= (nbr_col + 1) * (max_len + 2))
		return (1);
	else
	{
		move_cursor(0, 0);
		ft_putendl_fd("No Space", get_tty(0));
		return (0);
	}
}
