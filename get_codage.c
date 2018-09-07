/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_codage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:28:54 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:28:56 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_arg_type	*get_codage(t_process *process, int arg_num)
{
	t_arg_type		*arg_type;
	int				codage_pc;
	unsigned int	codage;
	int				i;
	int				shift;

	i = 0;
	shift = 6;
	codage_pc = (process->pc + 1) % MEM_SIZE;
	codage = conv_hex(&g_game.board[codage_pc], 1);
	arg_type = ft_strnew(arg_num);
	while (i < arg_num)
	{
		arg_type[i] = (codage >> shift) & 3;
		if (arg_type[i] == REG_CODE)
			arg_type[i] = T_REG;
		else if (arg_type[i] == DIR_CODE)
			arg_type[i] = T_DIR;
		else if (arg_type[i] == IND_CODE)
			arg_type[i] = T_IND;
		shift -= 2;
		i++;
	}
	return (arg_type);
}

bool		codage_valid(t_arg_type *arg_type, t_arg_type *ref, int arg_num)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (i < arg_num)
	{
		if ((arg_type[i] & ref[i]) > 0)
			check++;
		i++;
	}
	return (check == arg_num ? 1 : 0);
}
