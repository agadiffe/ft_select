/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 22:05:47 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/29 03:32:58 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
		ft_putendl("right");
	else
		ft_putendl("left");
}

static void		handle_del(t_elem *list)
{
	(void)list;
}

static void		handle_return(t_elem *list, int nbr_elem)
{
	t_elem	*tmp;
	int		i;

	i = 0;
	restore_backup_term(singleton_backup());
	tmp = list;
	while (++i < nbr_elem)
	{
		if (tmp->selected)
		{
			ft_putstr(tmp->name);
			ft_putchar(' ');
		}
		tmp = tmp->next;
	}
	ft_putchar('\b');
	free_list(list, nbr_elem);
	exit(0);
}

void			free_list(t_elem *list, int nbr_elem)
{
	t_elem	*tmp;

	while (--nbr_elem)
	{
		tmp = list->next;
		ft_memdel((void *)&list);
		list = tmp;
	}
}

void			handle_key(t_elem *list, int nbr_elem)
{
	char	*buf;
	int		key;

	buf = ft_strnew(4);
	while (42)
	{
		clear_all_screen();
		print_arg_list(list, nbr_elem);
		if (read(0, buf, 3) == -1)
			ft_error("Read error", 1);
		if ((key = is_esc(buf)))
			break ;
		else if ((key = is_return(buf)))
			handle_return(list, nbr_elem);
		else if ((key = is_del(buf)))
			handle_del(list);
		else if ((key = is_arrow(buf)))
			handle_arrow(list, key);
		else if ((key = is_space(buf)))
			handle_space(list);
		ft_bzero(buf, ft_strlen(buf));
	}
}
