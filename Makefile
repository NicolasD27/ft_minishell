# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nidescre <nidescre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 12:47:27 by nidescre          #+#    #+#              #
#    Updated: 2021/03/14 17:33:00 by nidescre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=  main.c quote.c utils.c chdir.c echo_pwd.c env.c env2.c \
			   env_options.c env_options2.c env_options3.c env_print.c\
			   env_utils.c gets.c setenv.c dollars.c redirections.c utils2.c\
			   signal.c exec.c command.c pipes.c termcap.c free.c parse.c


OBJS		= ${SRCS:.c=.o}

NAME		= minishell

CC			= cc
RM			= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} minishell.h
			make -C libft/ re
			cp libft/libft.a .
			make -C libft/ fclean
			gcc ${CFLAGS} -o ${NAME} ${OBJS} libft.a -ltermcap 

all:		${NAME}

clean:
			${RM} ${OBJS} libft.a

fclean:		clean
			${RM} ${NAME}

re:			fclean all
