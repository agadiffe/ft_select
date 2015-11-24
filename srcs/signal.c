/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/31 15:29:30 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/11 00:44:40 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <signal.h>

static void		handle_sig(int sig)
{
	int		enought_space;

	if (sig == SIGINT)
	{
		clear_all_screen();
		restore_backup_term(get_backup());
		get_tty(1);
		exit(1);
	}
	else if (sig == SIGWINCH)
	{
		clear_all_screen();
		enought_space = check_window_size(get_list(0, NULL));
		if (enought_space)
			print_arg_list(get_list(0, NULL));
	}
}

void			check_signal(void)
{
	signal(SIGWINCH, &handle_sig);
	signal(SIGINT, &handle_sig);
}
