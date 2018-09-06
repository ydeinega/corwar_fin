/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakdowns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:49:19 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/06 20:43:24 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "../op.h"

static int			get_total(void)
{
	int				res;
	int				i;

	i = -1;
	res = 0;
	while (++i < g_game.players)
		res += g_game.player[i].lives_in_curr;
	return (res);
}

static void			curr_breakdown(WINDOW *win, int *y, int x, int total)
{
	t_player		*pl;
	int				i;
	int				j;
	int				count;

	count = 0;
	i = -1;
	pl = g_game.player;
	while (++i < g_game.players)
	{
		if ((j = -1) && i == 0)
			mvwprintw(win, *y, (*y += 2) * 0 + x, "[");
		if (pl[i].lives_in_curr > 0)
			wattron(win, COLOR_PAIR(i + 1));
		while (((total > 0 && ++j < 50 * pl[i].lives_in_curr / total) ||
			(total == 0 && ++j < 50 / g_game.players)) && (count += 1))
			wprintw(win, "-");
		while (i == g_game.players - 1 && count++ < 50)
			wprintw(win, "-");
		wattroff(win, COLOR_PAIR(i + 1));
	}
	wprintw(win, "]");
}

void				draw_breakdowns(WINDOW *win, int *y, int x)
{
	mvwprintw(win, *y, x, "Live breakdown for current period :");
	*y += 1;
	curr_breakdown(win, y, x, get_total());
}
