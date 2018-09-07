/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 20:34:21 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/07 20:41:45 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		draw_frame(WINDOW *win)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	unset_colors(win);
	mvwprintw(win, 0, 0, "");
	wattron(win, A_REVERSE | A_BLINK);
	while (++j < 64 * 4 + 1)
		wprintw(win, " ");
	while (++i < 67)
	{
		mvwprintw(win, i, 0, " ");
		mvwprintw(win, i, 64 * 3 + 3, " ");
		mvwprintw(win, i, 64 * 4, " ");
	}
	j = 0;
	mvwprintw(win, i, 0, " ");
	while (++j < 64 * 4 + 1)
		wprintw(win, " ");
	wattroff(win, A_REVERSE | A_BLINK);
	wrefresh(win);
}

void		draw_map(WINDOW *win)
{
	int		i;
	int		y;
	char	*buff;

	i = -1;
	y = 2;
	buff = NULL;
	draw_frame(win);
	mvwprintw(win, 2, 2, "");
	unset_colors(win);
	while (++i < MEM_SIZE)
	{
		ft_strdel(&buff);
		check_color(i, g_game.player, win);
		wprintw(win, "%s", (buff = ft_itoa_base_mod(g_game.board[i], 16, 2)));
		wattroff(win, A_REVERSE | A_BLINK);
		i % 64 == 63 && i > 0 &&
			(y += 1) ? mvwprintw(win, y, 2, "") : wprintw(win, " ");
	}
	ft_strdel(&buff);
	wrefresh(win);
}
