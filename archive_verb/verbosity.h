#ifndef VERBOSITY_H
# define VERBOSITY_H
# include "corewar.h"

typedef struct			s_list_pc
{
	int					pc_prev;
	int					pc_new;
	int					move;
	unsigned char		*line;//malloc
	struct s_list_op	*next;
}						t_list_pc;


//op_tab[opcode - 1].arg_num - это кол-во аргументов 
typedef struct			s_list_op
{
	int					proc_num;
	int					opcode;
	t_arg_type			*arg_type;//malloc
	int					*arg;//malloc
	struct s_list_op	*next;
}						t_list_op;

typedef struct			s_list_death
{
	int					proc_num;
	int					cycles_not_live;
	struct s_list_op	*next;
}						t_list_death;

typedef struct 			s_verb
{
	int					cycle;//текущий цикл
	int					ctd;//cycle to die
	t_list_op			*op;//лист операций
	t_list_pc			*pc;//лист движения каретки
	t_list_death		*death;//лист смертей
}						t_verb;

t_verb					g_verb;
void					initialize_verb(void);
void					start_verb(int cycle, int ctd);//удалить все листы и посетить на налл, копировать cycle и cycle to die
void					verb_mode(int number_v);
void					introduce_contestants(void);
void					verb_add_pc_move(int pc_prev, int pc_new, int move, unsigned char *board);
void					verb_add_death(int proc_num, int cycles_not_live);
//void					verb_add_op(t_process *proc, t_arg_type *arg_type, int *arg);

#endif
