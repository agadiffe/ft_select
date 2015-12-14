/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/31 15:29:30 by agadiffe          #+#    #+#             */
/*   Updated: 2015/12/14 01:17:58 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>

static void		handle_sig(int sig)
{
	struct termios	term;
	int				enought_space;

	if (sig == SIGTSTP)
	{
		clear_all_screen();
		restore_backup_term(get_backup());
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
	}
	else if (sig == SIGCONT)
	{
		check_signal();
		init_term();
		set_term_in_non_canonic_mode(&term, get_backup());
		move_cursor(0, 0);
		clear_all_screen();
		enought_space = check_window_size(get_list(0, NULL));
		if (enought_space)
			print_arg_list(get_list(0, NULL));
	}
	else if (sig == SIGWINCH)
	{
		clear_all_screen();
		enought_space = check_window_size(get_list(0, NULL));
		if (enought_space)
			print_arg_list(get_list(0, NULL));
	}
	else
	{
		clear_all_screen();
		restore_backup_term(get_backup());
		free_list(get_list(0, NULL));
		get_tty(1);
		exit(1);
	}
}

void			check_signal(void)
{
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, &handle_sig);
		i++;
	}
}
