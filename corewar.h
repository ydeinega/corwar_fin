/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 19:41:59 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/27 19:42:02 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "op.h"
# include "./libft/libft.h"
# include <ncurses.h>
// # include "./verbosity/verbosity.h"
# define HEX "0123456789abcdef"

typedef struct			s_change
{
	int					player;
	unsigned char		*value;
	unsigned int		pos;
	int					len;
	struct s_change		*next;
}						t_change;

typedef struct 			s_chlist
{
	t_change			*list;
	int 				counter;
	struct s_chlist		*next;
}						t_chlist;

typedef struct			s_process
{
	int					num;
	int					player;
	bool				carry;
	bool				live;
	int					lives_ctd;
	int					pc;
	int					prev;//ADD//если размножение каретки, что делать???
	int					pc_change;//ADD//если размножение каретки, что делать???
	int					cycles_not_live;
	int					opcode;
	int					cycles_to_exec;
	unsigned int		reg[REG_NUMBER];
	struct s_process	*next;
}						t_process;

typedef	struct			s_player
{
	int					num;
	char				*name;//malloc
	char				*comment;//malloc
	unsigned char		*comms;//malloc
	int					start;
	unsigned int		len;
	int					last_live;
	int					lives_in_curr;
	int					lives_in_curr_all;
}						t_player;

typedef struct			s_lst_champs
{
	int					num;
	int					error;
	bool				n_flag;
	char				*file_name;//no malloc
	int					fd;
	unsigned int		magic;
	unsigned int		size;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		*comms;//instructions malloc!
	struct s_lst_champs	*next;//no malloc
}						t_lst_champs;

typedef	struct			s_parse
{
	int					players;
	int					proc_num;
	int					death_num;
	int					cycle;
	int					ctd;
	int					ctd_cur;
	int					checks;
	int					player_last_live;
	t_lst_champs		*champ;//free
	t_player			*player;//free
	unsigned char		*board;//free
	t_process			*proc;//free
	bool				end;
	bool				dump;
	bool				visu;
	bool				v;
	bool				a;//new
	int					nbr_cycles;
	int					nbr_cycles_visu;
	int					number_v;
	WINDOW				*win;//free???
	t_change			*change;//free
	t_chlist			*chlist;
	int 				timeout;
}						t_parse;

typedef	struct 			s_op
{
	char				*op;
	int					arg_num;
	t_arg_type			arg[3];
	int					opcode;
	int					cycles_to_exec;
	char				*descript;
	bool				codage;
	bool				carry;
	int					label;
}						t_op;

# include "./verbosity/verbosity.h"
# include "./visu/visu.h"

typedef	void			(*funcptr)(t_process *process, unsigned int *arg, t_arg_type *arg_type);
t_parse					g_game;
extern char				*g_usage[19];
extern char				*g_error[16];
extern funcptr			g_command[16];
t_op					g_op_tab[17];
void					usage(void);
void					error(int num);
void					parse_args(int argc, char **argv);
void					validate_dump(int argc, char **argv, int *i);
bool					validate_num(char *str);
bool					check_if_int(char *str);
void					validate_visu(int argc, char **argv, int *i);
void					validate_verbal(int argc, char **argv, int *i);
void					validate_champ(int argc, char **argv, int *i);
int						validate_champ_num(int argc, char **argv, int *i);
void					check_double_positions(int num);
void					champ_position(t_lst_champs *champ, int num);
t_lst_champs			*new_champ(char *file_name, int num, bool n_flag);
void					add_champ(t_lst_champs **head, t_lst_champs *new);
void					set_blank_positions(void);
void					check_positions(void);
void					sort_champs(void);
t_lst_champs			*swap_champs(t_lst_champs *tmp, t_lst_champs *prev);
void					parse_champs(void);
void					read_champs_info(t_lst_champs *champ);
unsigned int			read_num(t_lst_champs *champ, int len);
void					read_string(t_lst_champs *champ, char *line, int len);
void					read_instructions(t_lst_champs *champ);
unsigned int			conv_hex(unsigned char *line, int length);
char					*ft_strljoin(char **s1, char **s2);
//char					*hex_line(unsigned char *line, int length);
//unsigned int			ft_atoi_base(char *str, long long base);
void					start_game(void);
t_player				*create_players(void);
unsigned char			*create_board(t_player *player);
void					dump(void);
t_process				*create_process(t_player *player);
t_process				*new_process(t_player *player, t_process *proc, int pc);
void					add_process(t_process **head, t_process *new);
//void					regcpy(unsigned int *dst, unsigned int *src, int len);
//void					regset(unsigned int *dst, unsigned int c, int len);
void					run_game(void);
bool					make_check(void);
bool					check_deaths(void);
bool					check_nbr_live(void);
void					run_processes(void);
void					exec_instruct(t_process *proc);//
void					read_next_instruct(t_process *proc);
// void					read_next_instruct(t_process *proc, int move, int base);
void					exec_live(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_ld(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_st(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_add(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_sub(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_and(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_or(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_xor(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_zjmp(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_ldi(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_sti(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_fork(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_lld(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_lldi(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_lfork(t_process *process, unsigned int *arg, t_arg_type *arg_type);
void					exec_aff(t_process *process, unsigned int *arg, t_arg_type *arg_type);
t_arg_type				*get_codage(t_process *process, int arg_num);
bool					codage_valid(t_arg_type *arg_type, t_arg_type *ref, int arg_num);
int						get_move(t_process *proc, t_arg_type *arg_type, unsigned int *arg);
unsigned int			*extract_arg(t_op op, int pc, t_arg_type *arg_type);
unsigned int			read_from_board(int pc, int length);
unsigned char			*extract_line(int pc, int length);
unsigned int			extract_ind(t_process *process, int delta, int base);
bool					arg_valid(t_arg_type *arg_type, unsigned int *arg, int arg_num);
unsigned int			arg_fin(t_process *process, unsigned int arg, t_arg_type arg_type);
void					store_value(t_process *proc, unsigned int value, int delta, int base);
unsigned char			*to_hex_str(unsigned int num);
void					clean_all(void);

void					print_champ(t_lst_champs *champ);//del
void					print_proc(t_process *proc);//del debug
void					print_players(t_player *player);//del
void					print_info_before_exec(t_process *tmp, int move);//
void					print_info_after_exec(t_process *tmp);//
void					print_codage(int codage, t_arg_type *arg_type, int arg_num);//
void					print_arg(unsigned int *argument, int opcode);
#endif
