/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_pc_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:41:24 by dgonor            #+#    #+#             */
/*   Updated: 2018/07/20 15:41:30 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

static unsigned char		*extract_pies_board(int pc_prev, int pc_new, int move, unsigned char *board)
{
//	ft_printf("40 SEGFOLT?\n");
	int 	i;
	int 	p;
	unsigned char	*pies_of_board;

	board = g_game.board;
	i = -1; //
	pc_new = 0;
	pies_of_board = (unsigned char *)malloc(sizeof(unsigned char) * move);
	i = -1;
	p = pc_prev - 1;
	while (++i < move)
		pies_of_board[i] = board[++p];
	p = 0;
	if (move)
	{
		while (i < move)
			pies_of_board[i++] = board[p++];
	}
	return (pies_of_board);
}

static void			lstback_pc_list(t_list_pc **lst, t_list_pc *add)
{
//	ft_printf("30 SEGFOLT?\n");
	t_list_pc	*tmp;

	tmp = NULL;
	if (lst && *lst && add)
	{
		tmp = *lst;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = add;
	}
}

static t_list_pc		*create_pc_list(int pc_prev, int pc_new, int move, unsigned char *board)
{
//	ft_printf("20 SEGFOLT?\n");
	t_list_pc	*new;

	if (!(new = (t_list_pc*)malloc(sizeof(t_list_pc) * 1)))
		return (NULL);
	new->pc_prev = pc_prev;
	new->pc_new = pc_new;
	new->move = move;
	new->line = extract_pies_board(pc_prev, pc_new, move, board);
	new->next = NULL;
	return (new);
}

void	verb_add_pc_move(int pc_prev, int pc_new, int move, unsigned char *board)
{
//	ft_printf("10 SEGFOLT?\n");
//		ADV 6 (0x059f -> 0x05a5) 0a 94 ff f4 0a 0b
	if (!g_verb.pc)
		g_verb.pc = create_pc_list(pc_prev, pc_new, move, board);
	else
		lstback_pc_list(&g_verb.pc, create_pc_list(pc_prev, pc_new, move, board));
}