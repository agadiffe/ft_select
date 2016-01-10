/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/31 15:29:30 by agadiffe          #+#    #+#             */
/*   Updated: 2016/01/10 19:59:47 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>

static void		handle_sigtstp(void)
{
	restore_backup_term(get_backup());
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

static void		handle_sigcont(void)
{
	struct termios	term;
	int				*enought_space;

	check_signal();
	init_term();
	set_term_in_non_canonic_mode(&term, get_backup());
	move_cursor(0, 0);
	clear_all_screen();
	enought_space = get_enought_space();
	*enought_space = check_window_size(get_list(0, NULL));
	if (*enought_space)
		print_arg_list(get_list(0, NULL));
}

static void		handle_sigwinch(void)
{
	int		enought_space;

	clear_all_screen();
	enought_space = get_enought_space();
	*enought_space = check_window_size(get_list(0, NULL));
	if (*enought_space)
		print_arg_list(get_list(0, NULL));
}

static void		handle_sig(int sig)
{
	if (sig == SIGTSTP)
		handle_sigtstp();
	else if (sig == SIGCONT)
		handle_sigcont();
	else if (sig == SIGWINCH)
		handle_sigwinch();
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
