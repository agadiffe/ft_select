/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:28:59 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/28 21:55:14 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <stdlib.h>
#include <term.h>

void	init_term(void)
{
	char	*name_term;
	int		success;

	if (!(name_term = getenv("TERM")))
		ft_error("Specify a terminal type with 'setenv/export TERM'", 1);
	success = tgetent(NULL, name_term);
	if (success < 0)
		ft_error("Could not access the termcap data base", 1);
	if (success == 0)
		ft_error("Terminal type is not defined", 1);
}

void	set_term_in_non_canonic_mode(t_data *term, struct termios *backup)
{
	if (tcgetattr(0, &term->info) == -1)
		ft_error("Can't get terminal info", 1);
	*backup = term->info;
	term->info.c_lflag &= ~(ICANON | ECHO);
	term->info.c_cc[VMIN] = 1;
	term->info.c_cc[VTIME] = 0;
	get_window_terminal_size(&term->column, &term->row);
	if (tcsetattr(0, TCSADRAIN, &term->info) == -1)
		ft_error("Can't set new terminal attribut", 1);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_ret);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_ret);
}
