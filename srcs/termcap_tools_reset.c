/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_tools_reset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 21:43:02 by agadiffe          #+#    #+#             */
/*   Updated: 2015/12/14 01:08:23 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <unistd.h>
#include <term.h>

int		ft_putchar_ret(int c)
{
	return (write(get_tty(0), &c, 1));
}

void	reset_default_term(struct termios *term)
{
	term->c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, term) == -1)
		ft_error("Can't restore default terminal mode", 1);
	tputs(tgetstr("te", NULL), 1, ft_putchar_ret);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_ret);
}

void	restore_backup_term(struct termios *backup)
{
	if (tcsetattr(0, 0, backup) == -1)
		ft_error("Can't restore terminal attribut", 1);
	tputs(tgetstr("te", NULL), 1, ft_putchar_ret);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_ret);
}
