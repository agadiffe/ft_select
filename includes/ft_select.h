/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agadiffe <agadiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 21:07:09 by agadiffe          #+#    #+#             */
/*   Updated: 2015/10/28 04:23:15 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include <termios.h>

# define UP_KEY			65
# define DOWN_KEY		66
# define RIGHT_KEY		67
# define LEFT_KEY		68

# define START_REVERSE_MODE		"mr"
# define END_REVERSE_MODE		"me"
# define START_UNDERLINING		"us"
# define END_UNDERLINING		"ue"

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
}					t_elem;

int					is_return(char *buf);
int					is_arrow(char *buf);
int					is_esc(char *buf);
int					is_space(char *buf);
int					is_del(char *buf);

#endif
