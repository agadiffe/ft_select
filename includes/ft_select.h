/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 21:07:09 by agadiffe          #+#    #+#             */
/*   Updated: 2015/11/26 03:46:38 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <term.h>

# define UP_KEY			65
# define DOWN_KEY		66
# define RIGHT_KEY		67
# define LEFT_KEY		68

typedef struct		s_win
{
	int				row_term;
	int				col_term;
}					t_win;

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
	int				pos_list;
	int				col_n;
}					t_elem;

/*
**	main.c
*/
struct termios		*get_backup(void);
int					get_tty(int close_fd);
void				free_list(t_elem *list);

/*
**	arrow_handle.c
*/
void				handle_arrow(t_elem *list, int key);

/*
**	key_handle.c
*/
void				handle_key(t_elem **list, struct termios *backup);
int					check_window_size(t_elem *list);

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
t_elem				*get_current_elem(t_elem *list);
int					get_nbr_elem_per_col(t_elem *list);
void				list_update_pos(t_elem *list, int elem_del);
int					list_get_max_len(t_elem *list);

/*
**	list_create_print.c
*/
t_elem				*get_list(int ac, char **av);
void				print_arg_list(t_elem *list);

/*
**	signal.c
*/
void				check_signal(void);

/*
**	termcap_init.c
*/
void				init_term(void);
void				set_term_in_non_canonic_mode(struct termios *term,
													struct termios *backup);

/*
**	termcap_tools_reset.c
*/
int					ft_putchar_ret(int c);
void				reset_default_term(struct termios *term);
void				restore_backup_term(struct termios *backup);

/*
**	termcap_tools_window.c
*/
void				clear_all_screen(void);
t_win				get_window_size(void);
void				move_cursor(int x, int y);

#endif
