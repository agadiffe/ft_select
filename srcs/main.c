/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 11:48:12 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/29 03:33:38 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <term.h>

struct termios	*singleton_backup(void)
{
	static struct termios	backup;

	return (&backup);
}

int				main(int ac, char **av)
{
	t_data			term;
	struct termios	*backup;
	t_elem			*list;

	if (ac < 2)
		ft_putendl("usage: ./ft_select arg1 arg2 ...");
	else
	{
		backup = singleton_backup();
		list = create_list(ac, av);
		init_term();
		set_term_in_non_canonic_mode(&term, backup);
		move_cursor(0, 0);
		handle_key(list, ac);
		free_list(list, ac);
		restore_backup_term(backup);
	}
	return (0);
}
