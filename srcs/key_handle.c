/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 22:05:47 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/11 00:43:19 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <unistd.h>

static t_elem	*get_current_elem(t_elem *list)
{
	t_elem	*tmp;

	tmp = list;
	while (tmp->cursor != 1)
		tmp = tmp->next;
	return (tmp);
}

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

static void		handle_space(t_elem *list)
{
	t_elem	*tmp;

	tmp = get_current_elem(list);
	tmp->cursor = 0;
	tmp->next->cursor = 1;
	tmp->selected = tmp->selected ? 0 : 1;
}

static void		handle_arrow(t_elem *list, int key)
{
	if (key == UP_KEY)
		handle_down_and_up(list, 1);
	else if (key == DOWN_KEY)
		handle_down_and_up(list, 0);
	else if (key == RIGHT_KEY)
		ft_putendl_fd("right", get_tty(0));
	else
		ft_putendl_fd("left", get_tty(0));
}

static void		list_update_pos(t_elem *list, int elem_del)
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
		}
		else
			tmp->pos_y -= 1;
		tmp = tmp->next;
		elem_del++;
	}
}

static int		handle_del(t_elem **list)
{
	t_elem	*tmp;
	int		nbr_elem;
	int		current_max_len;

	current_max_len = list_get_max_len(*list);
	nbr_elem = (*list)->prev->pos_list;
	if (nbr_elem == 1)
		return (1);
	tmp = get_current_elem(*list);
	if (tmp->pos_list == 1)
		(*list) = (*list)->next;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	tmp->next->cursor = 1;
	list_update_pos(*list, tmp->pos_list);
	if (current_max_len != list_get_max_len(*list))
		check_window_size(*list);
	ft_memdel((void **)&tmp);
	clear_all_screen();
	return (0);
}

static void		handle_rtn(t_elem *list, struct termios *backup)
{
	t_elem	*tmp;
	int		first_print;
	int		nbr_elem;

	nbr_elem = list->prev->pos_list;
	first_print = 1;
	restore_backup_term(backup);
	tmp = list;
	while (nbr_elem--)
	{
		if (tmp->selected)
		{
			if (!first_print)
				ft_putchar(' ');
			ft_putstr(tmp->name);
			first_print = 0;
		}
		tmp = tmp->next;
	}
	free_list(list);
}

void			free_list(t_elem *list)
{
	t_elem	*tmp;
	int		nbr_elem;

	nbr_elem = list->prev->pos_list;
	while (nbr_elem--)
	{
		tmp = list->next;
		ft_memdel((void **)&list);
		list = tmp;
	}
}

int				list_get_max_len(t_elem *list)
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

int				list_get_max_col_len(t_elem *list, int col)
{
	int		max_len;
	t_elem	*tmp;

	tmp = list;
	while (tmp->col_n != col)
		tmp = tmp->next;
	max_len = tmp->len;
	tmp = tmp->next;
	while (tmp->col_n == col)
	{
		if (max_len < tmp->len)
			max_len = tmp->len;
		tmp = tmp->next;
	}
	return (max_len);
}

static int		check_key(t_elem **list, struct termios *backup, char *buf)
{
	int		key;

	if ((key = is_return(buf)))
	{
		ft_strdel(&buf);
		handle_rtn(*list, backup);
		exit(0);
	}
	else if ((key = is_del(buf)))
	{
		if (handle_del(list))
			return (-1);
	}
	else if ((key = is_arrow(buf)))
		handle_arrow(*list, key);
	else if ((key = is_space(buf)))
		handle_space(*list);
	else
		return (0);
	return (key);
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

void			handle_key(t_elem **list, struct termios *backup)
{
	char	*buf;
	int		update_screen;
	int		enought_space;

	enought_space = check_window_size(*list);
	buf = ft_strnew(4);
	update_screen = 1;
	while (!is_esc(buf))
	{
		if (update_screen && enought_space)
			print_arg_list(*list);
		ft_bzero(buf, ft_strlen(buf));
		if (read(0, buf, 3) == -1)
			ft_error("Read error", 1);
		if ((update_screen = check_key(list, backup, buf)) == -1)
			break ;
	}
	ft_strdel(&buf);
}
