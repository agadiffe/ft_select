/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_tools_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:52:10 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/28 22:02:03 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <term.h>

/*
int		get_window_terminal_size(int *column, int *row)
{
	struct winsize		win;

	if (ioctl(0, TIOCGWINSZ, &win) == -1)
		return (0);
	*column = win.ws_col;
	*row = win.ws_row;
	return (1);
}
*/

void	get_window_terminal_size(int *column, int *row)
{
	*column = tgetnum("co");
	*row = tgetnum("li");
	if (*column == -1 || *row == -1)
		ft_error("Can't get window terminal size", 1);
}

void	clear_all_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar_ret);
}

void	move_cursor(int x, int y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putchar_ret);
}

