/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 00:42:04 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/13 17:52:52 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

struct termios	init_termcap(void)
{
	char			*term_name;
	struct termios	termios_new;
	struct termios	termios_backup;

	term_name = getenv("TERM");
	tgetent(NULL, term_name);
	bzero(&termios_new, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &termios_backup);
	termios_new = termios_backup;
	termios_new.c_lflag &= ~(ICANON);
	termios_new.c_lflag &= ~(ECHO);
	termios_new.c_cc[VMIN] = 1;
	termios_new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);
	return (termios_backup);
}

void			get_termcap(char *s)
{
	char *cl_string;

	cl_string = tgetstr(s, NULL);
	tputs(cl_string, 1, &ft_putchar);
}
