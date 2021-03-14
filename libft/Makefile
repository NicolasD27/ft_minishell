# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nidescre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 13:59:59 by nidescre          #+#    #+#              #
#    Updated: 2019/10/29 14:39:21 by nidescre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ${shell find . -name '*.c' ! -name '*bonus.c'} 
SRCSB		= ${shell find . -name '*bonus.c'}

OBJS		= ${SRCS:.c=.o} 
OBJSB		= ${SRCSB:.c=.o}

NAME		= libft.a

CC			= cc
RM			= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} libft.h
			ar rc ${NAME} ${OBJS}

all:			${NAME}

bonus:		${OBJS} ${OBJSB} libft.h
			ar rc ${NAME} ${OBJS} ${OBJSB}
clean:
					${RM} ${OBJS} ${OBJSB}

fclean:		clean
					${RM} ${NAME}

re:				fclean all
