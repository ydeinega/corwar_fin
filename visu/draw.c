/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:23:41 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/08/28 20:11:12 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"



static void		check_color(int pos, t_player *players, WINDOW *win)
{
	int			i;
	int			st;
	int			len;

	i = -1;
	
	while (++i < g_game.players)
	{
		st = players[i].start;
		len = players[i].len;
		if (pos == st) {
			wattron(win, A_REVERSE | A_BLINK);
			wattron(win, COLOR_PAIR(i + 1));
		}
		else if (pos == st + len + 1)
			unset_colors(win);
	}
}

static void			draw_frame(WINDOW *win)
{
	int				i;
	int				j;

	i = 0;
	j = -1;
	unset_colors(win);
	mvwprintw(win, 0, 0, "");
	wattron(win, A_REVERSE | A_BLINK);
	while (++j < 64 * 4 + 1)
		wprintw(win, " ");
	while (++i < 67) {
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



static void			draw_procs(WINDOW *win)
{
	t_process		*curr;
	char			*buff;
	unsigned char	*map;

	wattroff(win, A_BOLD);
	buff = NULL;
	curr = g_game.proc;
	map = g_game.board;
	while (curr)
	{
		if (curr->live) {
			if (curr->prev >= 0)
			{
				wattroff(win, A_REVERSE | A_BLINK);
				write_value(curr->player, map[curr->prev % MEM_SIZE], curr->prev % MEM_SIZE, win);
			}
			wattron(win, A_REVERSE | A_BLINK);
			write_value(curr->player, map[curr->pc % MEM_SIZE], curr->pc % MEM_SIZE, win);
			wattroff(win, A_REVERSE | A_BLINK);
		}
		curr = curr->next;
	}
}

void				draw_map(WINDOW *win)
{
	int				i;
	int				y;
	char			*buff;
	unsigned char	*map;

	i = -1;
	y = 2;
	buff = NULL;
	map = g_game.board;
	draw_frame(win);
	mvwprintw(win, 2, 2, "");
	unset_colors(win);
	while (++i < MEM_SIZE)
	{
		ft_strdel(&buff);
		check_color(i, g_game.player, win);
		wprintw(win, "%s", (buff = ft_itoa_base_mod(map[i], 16, 2)));
		wattroff(win, A_REVERSE | A_BLINK);
		i % 64 == 63 && i > 0 && (y += 1) ? mvwprintw(win, y, 2, "") : wprintw(win, " ");
	}
	ft_strdel(&buff);
	wrefresh(win);
}

void				draw_all(WINDOW *win)
{
	int				y;

	y = 2;
	unset_colors(win);
	draw_frame(win);
	draw_info(win, &y);
	// draw_changes(win);
	handle_changes();
	draw_procs(win);
	unset_colors(win);
	// box(win, 0, 0);
	wrefresh(win);
}
