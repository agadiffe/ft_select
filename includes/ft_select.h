/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 21:07:09 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/29 03:19:45 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include <term.h>

# define UP_KEY			65
# define DOWN_KEY		66
# define RIGHT_KEY		67
# define LEFT_KEY		68

typedef struct		s_data
{
	struct termios	info;
	int				column;
	int				row;
}					t_data;

typedef struct		s_elem
{
	struct s_elem	*next;
	struct s_elem	*prev;
	char			*name;
	int				len;
	int				pos_x;
	int				pos_y;
	int				selected;
	int				cursor;
}					t_elem;

struct termios		*singleton_backup(void);

/*
**	key_function.c
*/
void				handle_key(t_elem *list, int nbr_elem);
void				free_list(t_elem *list, int nbr_elem);

/*
**	key_is.c
*/
int					is_return(char *buf);
int					is_arrow(char *buf);
int					is_esc(char *buf);
int					is_space(char *buf);
int					is_del(char *buf);

/*
**	list_function.c
*/
t_elem				*create_list(int ac, char **av);
void				display_single_list_elem(t_elem *elem);
void				print_arg_list(t_elem *list, int nbr_elem);

/*
**	termcap_init.c
*/
void				init_term(void);
void				set_term_in_non_canonic_mode(t_data *term,
													struct termios *backup);

/*
**	termcap_tools_reset.c
*/
int					ft_putchar_ret(int c);
void				reset_default_term(t_data *term);
void				restore_backup_term(struct termios *backup);

/*
**	termcap_tools_window.c
*/
void				clear_all_screen(void);
void				get_window_terminal_size(int *column, int *row);
void				move_cursor(int x, int y);

#endif
