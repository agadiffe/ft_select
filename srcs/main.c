/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 11:48:12 by agadiffe          #+#    #+#             */
/*   Updated: 2015/12/13 05:11:34 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <term.h>
#include <unistd.h>
#include <fcntl.h>

int				get_tty(int close_fd)
{
	static int	fd;

	if (!fd)
	{
		if ((fd = open("/dev/tty", O_WRONLY)) == -1)
			ft_error("Can't open tty", 1);
	}
	if (close_fd)
		close(fd);
	return (fd);
}

struct termios	*get_backup(void)
{
	static struct termios	backup;

	return (&backup);
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

int				main(int ac, char **av)
{
	struct termios	term;
	struct termios	*backup;
	t_elem			*list;

	if (ac < 2)
		ft_putendl("usage: ./ft_select arg1 arg2 ...");
	else
	{
		check_signal();
		backup = get_backup();
		list = get_list(ac, av);
		init_term();
		set_term_in_non_canonic_mode(&term, backup);
		move_cursor(0, 0);
		handle_key(&list, backup);
		free_list(list);
		restore_backup_term(backup);
		get_tty(1);
	}
	return (0);
}
