# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badrien <badrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by badrien           #+#    #+#              #
#    Updated: 2021/11/17 12:35:25 by badrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = 	pipex.c utils.c ft_split.c pipex_utils.c
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
			@rm -f outfile outfile2
			
re:			fclean all
		
exec:		re
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)

t1:			re
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			./$(NAME) infile "ls -l" "wc -l" outfile
			< infile ls -l | wc -l > outfile2

t2:			re
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			./$(NAME) infile "grep a1" "wc -w" outfile
			< infile grep a1 | wc -w > outfile2