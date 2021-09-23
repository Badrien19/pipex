# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badrien <badrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by user42            #+#    #+#              #
#    Updated: 2021/09/23 13:59:35 by badrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = 	main.c utils.c ft_split.c
OBJS = $(SRC:.c=.o)
NAME = pipex

all : $(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) ${OBJS} -o $(NAME)
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

clean:
			@rm -f *.o

fclean:	clean
			@rm -f $(NAME)
			@rm -f a.aout
			
re:			fclean all
		
exec:		re
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
