/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 11:48:12 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/28 05:00:55 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>

int		ft_putchar_ret(int c)
{
	return (write(1, &c, 1));
}

void	clear_all_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar_ret);
}

void	reset_default_term(t_data *term)
{
	term->info.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, TCSADRAIN, &term->info) == -1)
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

void	print_arg_list(t_elem *list, int nbr_elem)
{
	t_elem	*tmp;

	tmp = list;
	while (--nbr_elem)
	{
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}

t_elem	*create_list(int ac, char **av)
{
	t_elem	*list;
	t_elem	*new;
	t_elem	*prev;
	int		i;

	list = (t_elem *)malloc(sizeof(t_elem));
	list->next = NULL;
	list->prev = NULL;
	list->name = av[1];
	list->len = ft_strlen(av[1]);
	list->pos_x = 0;
	list->pos_y = 0;
	list->selected = 1;
	i = 2;
	prev = list;
	while (i < ac)
	{
		new = (t_elem *)malloc(sizeof(t_elem));
		prev->next = new;
		new->prev = prev;
		new->name = av[i];
		new->len = ft_strlen(av[i]);
		new->pos_x = 0;
		new->pos_y = i - 1;
		new->selected = 0;
		prev = new;
		i++;
	}
	new->next = list;
	return (list);
}

void	get_key(void)
{
	char	*buf;
	int		key;

	buf = ft_strnew(4);
	while (read(0, buf, 3))
	{
		if ((key = is_esc(buf)))
			break ;
		else if ((key = is_del(buf)))
			ft_putendl("del");
		else if ((key = is_arrow(buf)))
			ft_putendl("arrow");
		else if ((key = is_space(buf)))
			ft_putendl("space");
		else if ((key = is_return(buf)))
			ft_putendl("return");
		ft_bzero(buf, ft_strlen(buf));
	}
}

int		main(int ac, char **av)
{
	t_data			term;
	struct termios	backup;
	t_elem			*list;

	if (ac < 2)
		ft_putendl("usage: ./ft_select arg1 arg2 ...");
	else
	{
		list = create_list(ac, av);
		init_term();
		set_term_in_non_canonic_mode(&term, &backup);
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_ret);
		print_arg_list(list, ac);
		get_key();
		restore_backup_term(&backup);
	}
	return (0);
}
