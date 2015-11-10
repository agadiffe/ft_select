/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_tools_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:52:10 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/31 21:31:09 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <term.h>
#include <sys/ioctl.h>

t_win	get_window_size(void)
{
	struct winsize		win;
	t_win				ws;

	if (ioctl(0, TIOCGWINSZ, &win) == -1)
		ft_error("Can't get window terminal size", 1);
	ws.row_term = win.ws_row;
	ws.col_term = win.ws_col;
	return (ws);
}

void	clear_all_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar_ret);
}

void	move_cursor(int x, int y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putchar_ret);
}
