/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:28:22 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:28:24 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int				get_length(t_arg_type arg_type, t_op op)
{
	int	length;

	length = 0;
	if (arg_type == T_REG)
		length = 1;
	else if (arg_type == T_DIR)
		length = op.label;
	else if (arg_type == T_IND)
		length = IND_SIZE;
	return (length);
}

unsigned int			*extract_arg(t_op op, int pc, t_arg_type *arg_type)
{
	int				i;
	int				length;
	int				pc_copy;
	unsigned int	*arg;
	unsigned char	*line;

	i = 0;
	length = 0;
	pc_copy = pc;
	pc = op.codage ? (pc + 2) % MEM_SIZE : (pc + 1) % MEM_SIZE;
	arg = (unsigned int *)malloc(sizeof(unsigned int) * op.arg_num);//if !line malloc failed
	line = NULL;
	while (i < op.arg_num)
	{
		length = arg_type ? get_length(arg_type[i], op) : op.label;
		line = extract_line(pc, length);//под вопросом
		arg[i] = conv_hex(line, length);
		free(line);
		i++;
		pc = (pc + length) % MEM_SIZE;//???
	}
	return (arg);
}

unsigned char		*extract_line(int pc, int length)
{
	int 			i;
	unsigned char	*line;

	i = 0;
	line = (unsigned char *)malloc(sizeof(unsigned char) * length);//if !line malloc failed
	while (i < length)
	{
		line[i] = g_game.board[pc];
		i++;
		pc = (pc + 1) % MEM_SIZE;
	}
	return (line);
}

unsigned int			extract_ind(t_process *process, int delta, int base)//BASE???
{
	unsigned char	*line;
	unsigned int	res;
	int				pc_new;

	line = NULL;
	res = 0;
	pc_new = 0;
	if (base)
	{
		if (process->opcode != 10 && process->opcode != 14)
			pc_new = (process->pc + ((short)delta % base)) % MEM_SIZE;
		else
			pc_new = (process->pc + (delta % base)) % MEM_SIZE;
	}
	else
	{
		if (process->opcode != 10 && process->opcode != 14)
			pc_new = (process->pc + (short)delta) % MEM_SIZE;
		else
			pc_new = (process->pc + delta) % MEM_SIZE;
	}
	if (pc_new < 0)
		pc_new = MEM_SIZE + pc_new;

	line = extract_line(pc_new, 4);
	//line = extract_line(process->pc, 4);
	res = conv_hex(line, 4);

	//del
	// int i;
	// i = 0;
	// if (g_game.cycle == 2510)
	// {
	// 	ft_printf("pc_new = %d\n", pc_new);
	// 	while (i < 4)
	// 	{
	// 		ft_printf("%02x ", line[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\nres = %d\n", res);
	// }
	//del

	free(line);
	return (res);
}

// unsigned int			extract_ind(int pc, int delta, int base)//BASE???
// {
// 	unsigned char	*line;
// 	unsigned int	res;
// 	int				pc_new;

// 	line = NULL;
// 	res = 0;
// 	pc_new = 0;
// 	if (base)
// 		pc_new = (pc + (delta % base)) % MEM_SIZE;
// 	else
// 		pc_new = (pc + delta) % MEM_SIZE;
// 	line = extract_line(pc, 4);
// 	res = conv_hex(line, 4);
// 	free(line);
// 	return (res);		
// }

unsigned int			arg_fin(t_process *process, unsigned int arg, t_arg_type arg_type)
{
	unsigned int	res;
	unsigned int	base;

	res = 0;
	base = IDX_MOD;
	if (arg_type == T_REG)
		res = process->reg[arg - 1];
	else if (arg_type == T_DIR)
		res = arg;
	else if (arg_type == T_IND)
	{
		if (process->opcode == 13)
			base = 0;
		res = extract_ind(process, (short)arg, (short)base);
	}
	return (res);
}
