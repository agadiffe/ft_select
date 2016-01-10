/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 22:05:47 by agadiffe          #+#    #+#             */
/*   Updated: 2016/01/10 19:58:41 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <unistd.h>

static void		handle_space(t_elem *list)
{
	t_elem	*tmp;

	tmp = get_current_elem(list);
	tmp->cursor = 0;
	tmp->next->cursor = 1;
	tmp->selected = tmp->selected ? 0 : 1;
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

void			handle_key(t_elem **list, struct termios *backup)
{
	char	*buf;
	int		update_screen;
	int		*enought_space;

	buf = ft_strnew(4);
	update_screen = 1;
	enought_space = get_enought_space();
	while (!is_esc(buf))
	{
		*enought_space = check_window_size(*list);
		if (update_screen && *enought_space)
			print_arg_list(*list);
		ft_bzero(buf, ft_strlen(buf));
		if (read(0, buf, 3) == -1)
			ft_error("Read error", 1);
		if (*enought_space
				&& (update_screen = check_key(list, backup, buf)) == -1)
			break ;
	}
	ft_strdel(&buf);
}
