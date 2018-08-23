#include "corewar.h"

t_process	*create_process(t_player *player)
{
	int			i;
	t_process	*proc;
	t_process	*tmp;

	i = 0;
	proc = NULL;
	tmp = NULL;
	while (i < g_game.players)
	{
		tmp = new_process(&player[i], NULL, player[i].start);
		add_process(&proc, tmp);
		i++;
	}
	return (proc);
}

t_process	*new_process(t_player *player, t_process *proc, int pc)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
	{
		perror("malloc() in new_process() failed ");
		error(-1);
	}
	new->num = ++g_game.proc_num;
	new->player = player ? player->num : proc->player;
	new->carry = player ? 0 : proc->carry;
	new->live = 1;
	new->lives_ctd = 0;
	new->pc = pc;
	new->prev = -1;//или 0
	new->cycles_not_live = 0;
	new->opcode = conv_hex(&g_game.board[pc], 1);
	new->cycles_to_exec = op_tab[new->opcode - 1].cycles_to_exec;
	new->next = NULL;
	if (proc)
		regcpy(new->reg, proc->reg, REG_NUMBER);
	else
	{
		regset(new->reg, 0, REG_NUMBER);
		new->reg[0] = (unsigned int)(~(player->num) + 1);
	}
	return (new);
}

void		add_process(t_process **head, t_process *new)
{
	t_process *tmp;

	tmp = NULL;
	if (head && new)
	{
		tmp = *head;
		new->next = tmp;
		*head = new;
	}
}

void		regcpy(unsigned int *dst, unsigned int *src, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
}

void		regset(unsigned int *dst, unsigned int c, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = c;
}
