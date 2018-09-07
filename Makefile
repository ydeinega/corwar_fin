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

HEADERS = ./verbosity/verbosity.h \
corewar.h \
op.h \
./visu/visu.h

FLAGS = -Wall -Wextra -Werror

VERB_PATH = ./verbosity/

VISU_PATH = ./visu/

VERB_SRCS = \
verb_del.c \
verb_deaths.c \
verb_op.c \
verb_pc_move.c \
verb_print.c \
verb_mode.c \
verb_comment_print.c

VISU_SRCS = \
breakdowns.c \
draw.c \
draw_info.c \
visual_init.c \
ft_itoa_base_mod.c \
handle_changes.c \
helpers.c \
draw_map.c

VERB = $(addprefix $(VERB_PATH), $(VERB_SRCS))

SRCS = \
main.c \
usage.c \
parse_args.c \
validate_champ.c \
new_champ.c \
validation.c \
parse_champs.c \
ft_strljoin.c \
start_game.c \
create_player_arr.c \
create_process.c \
new_process.c \
conv_hex.c \
run_game.c \
run_processes.c \
instruct_1_4.c \
instruct_5_8.c \
instruct_9_12.c \
instruct_13_16.c \
instruct_info.c \
exec_instruct.c \
get_codage.c \
get_move.c \
extract_arg.c \
extract_ind.c \
read_from_board.c \
store_value.c \
clean_all.c 

VISU = $(addprefix $(VISU_PATH), $(VISU_SRCS))

OBJS = $(SRCS:.c=.o)

VERB_OBJS = $(VERB_SRCS:.c=.o)

VISU_OBJS = $(VISU_SRCS:.c=.o)

cor:
	@make -C libft
	gcc $(SRCS) $(VERB) $(VISU) $(FLAGS) -I $(HEADERS) -c 
	gcc $(FLAGS) $(OBJS) $(VERB_OBJS) $(VISU_OBJS) $(LIB) -o $(NAME) -lncurses
	@echo "\x1b[35mYour PROGRAM has been successfully created!\x1b[0m"

clean:
	@make -C libft clean
	rm -rf $(OBJS) $(VERB_OBJS) $(VISU_OBJS)
	@echo "\x1b[36mObject files have been deleted!\x1b[0m"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo "\x1b[32mExecutable files have been deleted!\x1b[0m"

re: fclean all
