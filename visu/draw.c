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

void	make_pause(void)
{
	while (true)
		if (getch() == 32)
			return ;
}

static void		check_color(int pos, t_player *players, WINDOW *win)
{
	int			i;
	int			st;
	int			len;
	// int			fd;

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
			wattroff(win, COLOR_PAIR(i + 1));
	}
	// close(fd);
}

void				unset_colors(WINDOW *win)
{
	int			i;

	i = -1;
	while (++i < 5)
		wattroff(win, COLOR_PAIR(i));
	wattron(win, COLOR_PAIR(5)); 
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
	int 			fd;
	int				tmp;

	fd = open("test.txt", O_RDWR | O_APPEND);
	buff = NULL;
	curr = g_game.proc;
	map = g_game.board;
	while (curr)
	{
		if ((tmp = getch()) != -1) {
			ft_putnbr_fd(tmp, fd);
			ft_putchar_fd('\n', fd);
			if (tmp == 32)
				make_pause();
		}
		if (curr->live) {
			if (curr->prev >= 0)
			{
				wattroff(win, A_REVERSE | A_BLINK);
				write_value(curr->player, map[curr->prev % MEM_SIZE], curr->prev % MEM_SIZE, win);
			}
			wattron(win, A_REVERSE | A_BLINK);
			write_value(curr->player, map[curr->pc % MEM_SIZE], curr->pc % MEM_SIZE, win);
			wattroff(win, A_REVERSE | A_BLINK);
			curr = curr->next;
		}
	}
	close(fd);
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
	int 			tmp;
	int				fd;

	fd = open("test.txt", O_RDWR | O_APPEND);
	map = g_game.board;
	// if (g_game.change == NULL || !(curr = g_game.change))
	// 	return ;
	curr = g_game.prev_change;
	wattroff(win, A_BOLD);
	while ((prev = curr))
	{
		if (getch() == 32)
			make_pause();
		i = -1;
		tmp = -1;
		// wattron(win, A_BOLD);
		while (++i < curr->len)
		{
			if (tmp == -1)
				tmp = curr->pos % MEM_SIZE;
			write_value(curr->player, curr->value[i], tmp, win);
			tmp = (tmp + 1) % MEM_SIZE;
		}
		// wattroff(win, A_BOLD);
		curr = curr->next;
		free(prev->value);
		free(prev);
	}
	wattron(win, A_BOLD);
	curr = g_game.change;
	while ((prev = curr))
	{
		i = -1;
		tmp = -1;
		// wattron(win, A_BOLD);
		while (++i < curr->len)
		{
			if (tmp == -1)
				tmp = curr->pos;
			write_value(curr->player, curr->value[i], tmp, win);
			tmp = (tmp + 1) % MEM_SIZE;
		}
		// wattroff(win, A_BOLD);
		curr = curr->next;
		// free(prev->value);
		// free(prev);
	}
	// box(win, 0, 0);
	// wrefresh(win);
	// usleep(3000);
	wattroff(win, A_BOLD);
	g_game.prev_change = g_game.change;
	g_game.change = NULL;
}

void				draw_all(WINDOW *win)
{
	draw_procs(win);
	draw_info(win);
	draw_changes(win);
	unset_colors(win);
	box(win, 0, 0);
	wrefresh(win);
}
