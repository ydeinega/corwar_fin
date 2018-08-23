# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/30 18:12:07 by ydeineha          #+#    #+#              #
#    Updated: 2018/06/30 18:12:09 by ydeineha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

LIB = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror -I. -c

SRCS = main.c usage.c parse_args.c validate_champ.c \
new_champ.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB): 
	@make -C libft

$(NAME): $(LIB)
	@gcc $(SRCS) $(FLAGS)
	@gcc $(OBJS) $(LIB) -o $(NAME)
	@echo "\x1b[35mYour PROGRAM has been successfully created!\x1b[0m"

clean:
	@make -C libft clean
	@rm -rf $(OBJS)
	@echo "\x1b[36mObject files have been deleted!\x1b[0m"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo "\x1b[32mExecutable files have been deleted!\x1b[0m"

re: fclean all
