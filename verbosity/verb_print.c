/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:25:43 by dgonor            #+#    #+#             */
/*   Updated: 2018/07/20 21:25:45 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

void		verb_print_lives(int p_num)
{
	int			i;
	int			num_players;
	t_player	*player;

	i = -1;
	num_players = g_game.players;
	player = g_game.player;
	while (++i < num_players)
	{
		if (player[i].num == -p_num)
			ft_printf("Player %i (%s) is said to be alive\n",
						i + 1, player[i].name);
	}
}

void		verb_print_ctd(int ctd)
{
	if ((2 & g_game.number_v) > 0)
		ft_printf("Cycle to die is now %i\n", ctd);
}

void		verb_print_cycles(int cycle)
{
	if ((2 & g_game.number_v) > 0)
		ft_printf("It is now cycle %i\n", cycle);
}

void		verb_print_death(int proc_num, int cycles_not_live)
{
	if ((8 & g_game.number_v) > 0)
	{
		ft_printf("Process %i ", proc_num);
		ft_printf("hasn't lived for %i cycles ", cycles_not_live);
		ft_printf("(CTD %i)\n", g_game.ctd);
	}
}

void		verb_print_pc(int pc_prev, int move, unsigned char *board)
{
	int		i;
	int		new;

	i = -1;
	new = pc_prev + move;
	if ((16 & g_game.number_v) > 0)
	{
		ft_printf("ADV %i ", move);
		pc_prev == 0 ? ft_printf("(0x0000 -> ") :
					ft_printf("(%#.4x -> ", pc_prev);
		if (new == 0)
			ft_printf("0x0000) ");
		else if (new < 0)
			ft_printf("%#.4x) ", MEM_SIZE + new);
		else
			ft_printf("%#.4x) ", new);
		while (++i < move)
			ft_printf("%.2x ", board[(pc_prev + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}
