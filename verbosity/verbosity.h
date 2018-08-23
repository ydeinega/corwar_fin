#ifndef VERBOSITY_H
# define VERBOSITY_H
# include "../corewar.h"

// typedef struct			s_process
// {
// 	int					num;
// 	int					player;
// 	bool				carry;
// 	bool				live;
// 	int					lives_ctd;
// 	int					pc;
// 	int					cycles_not_live;
// 	int					opcode;
// 	int					cycles_to_exec;
// 	unsigned int		reg[REG_NUMBER];
// 	struct s_process	*next;
// }						t_process;

typedef struct			s_list_pc
{
	int					pc_prev;
	int					pc_new;
	int					move;
	unsigned char		*line;//malloc
	struct s_list_pc	*next;
}						t_list_pc;

typedef struct			s_list_op
{
	int					proc_num;
	int					opcode;
	int					arg_num;
	t_arg_type			*arg_type;//malloc
	int					*arg;//malloc
	bool				carry;
	int					pc;
	struct s_list_op	*next;
}						t_list_op;

typedef struct			s_list_death
{
	int					proc_num;
	int					cycles_not_live;
	struct s_list_death	*next;
}						t_list_death;

typedef struct 			s_verb
{
	int					cycle;//текущий цикл
	int					ctd;//cycle to die
	bool				ctd_change; // везде подправить
	t_list_op			*op;//лист операций
	t_list_pc			*pc;//лист движения каретки
	t_list_death		*death;//лист смертей
}						t_verb;


t_verb					g_verb;
void					initialize_verb(void);
void					start_verb(void);//удалить все листы и посетить на налл, копировать cycle и cycle to die
void					verb_mode(int number_v);
void					introduce_contestants(void);
void					verb_add_pc_move(int pc_prev, int pc_new, int move, unsigned char *board);
void					verb_add_death(int proc_num, int cycles_not_live);
void					verb_add_op(t_process *proc, t_arg_type *arg_type, unsigned int *arg);
//void					verb_print_essent(void); DELL
void					verb_print_lives(int p_num);
void					verb_print_cycles(int cycle);
void					verb_print_ctd(int ctd);
void					verb_print_op(t_process *proc, t_arg_type *arg_type, unsigned int *arg);
void					verb_print_death(int proc_num, int cycles_not_live);
void					verb_print_pc(int pc_prev, int pc_new, int move, unsigned char *board);
void					verb_comment_print(t_list_op *op);

#endif
