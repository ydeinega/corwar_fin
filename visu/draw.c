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
	//int			fd;

	i = -1;
	//fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND);
	while (++i < g_game.players)
	{
		st = players[i].start;
		len = players[i].len;
		if (pos == st)
			wattron(win, A_REVERSE | A_BLINK);
		if (pos >= st && pos < st + len)
			wattron(win, COLOR_PAIR(i + 1));
		else if (pos >= st + len && (i + 1 == g_game.players || pos <= players[i + 1].start))
		{
			if (i == 0)
				wattroff(win, COLOR_PAIR(1));
			else
				wattroff(win, COLOR_PAIR(i));
		}
	}
}

static void			write_value(int pl, unsigned char val, int pos, WINDOW *win)
{
	int			x;
	int			y;
	char		*buff;

	y = pos / 64 + 1;
	x = (pos % 64) * 3 + 1;
	wattron(win, COLOR_PAIR(pl));
	mvwprintw(win, y, x, (buff = ft_itoa_base_mod(val, 16, 2)));
	wattroff(win, A_REVERSE | A_BLINK);
	pos % 64 == 63 ? wprintw(win, "\n ") : wprintw(win, " ");
	ft_strdel(&buff);
}

static void			draw_procs(WINDOW *win)
{
	t_process		*curr;
	char			*buff;
	unsigned char	*map;

	buff = NULL;
	curr = g_game.proc;
	map = g_game.board;
	while (curr)
	{
		if (curr->live) {
			if (curr->prev >= 0)
			{
				wattroff(win, A_REVERSE | A_BLINK);
				write_value(curr->player, map[curr->prev], curr->prev, win);
			}
			wattron(win, A_REVERSE | A_BLINK);
			write_value(curr->player, map[curr->pc], curr->pc, win);
			wattroff(win, A_REVERSE | A_BLINK);
			curr = curr->next;
		}
	}
}

void				draw_map(WINDOW *win)
{
	int				i;
	char			*buff;//unsigned char ???
	unsigned char	*map;

	i = -1;
	buff = NULL;
	map = g_game.board;
	mvwprintw(win, 0, 0, "\n ");
	while (++i < MEM_SIZE)
	{
		ft_strdel(&buff);
		check_color(i, g_game.player, win);
		wprintw(win, "%s", (buff = ft_itoa_base_mod(map[i], 16, 2)));
		wattroff(win, A_REVERSE | A_BLINK);
		i % 64 == 63 && i > 0 ? wprintw(win, "\n ") : wprintw(win, " ");
	}
	ft_strdel(&buff);
	box(win, 0, 0);
	wrefresh(win);
}

static void				draw_changes(WINDOW *win)
{
	t_change		*curr;
	t_change		*prev;
	unsigned char	*map;
	int				i;
	// int				j;
	// int				fd = open("testlog.txt", O_RDWR | O_APPEND);

	map = g_game.board;
	// i = 0;
	if (g_game.change == NULL || !(curr = g_game.change))
		return ;
	while ((prev = curr))
	{
		i = -1;
		// while (++j < 4) {
		// 	ft_putstr_fd(ft_itoa_base_mod(curr->value[j], 16, 2), fd);
		// 	ft_putstr_fd(" ", fd);
		// }
		// ft_putstr_fd("\n", fd);
		while (++i < curr->len)
		{
			write_value(curr->player, curr->value[i], curr->pos, win);
			curr->pos = (curr->pos + 1) % MEM_SIZE;
		}
		curr = curr->next;
		free(prev->value);
		free(prev);
	}
	g_game.change = NULL;
	// close(fd);
}

// void				draw_info(WINDOW *win)
// {
// 	wattron(win, COLOR_PAIR(0));
// 	wattroff(win, A_REVERSE | A_BLINK);
// 	mvwprintw(win, 1, 64 * 3 + 3, "** RUNNING **\n\n");
// 	wprintw(win, "%s\n\n\n", "Cycles/second limit : 8000");
// 	wprintw(win, "Cycle : %d\n\n", g_game.cycle);

// }

void				draw_all(WINDOW *win)
{
	// if (0 != 0)
	draw_changes(win);
	draw_procs(win);
	draw_info(win);
	box(win, 0, 0);
	wrefresh(win);
}
