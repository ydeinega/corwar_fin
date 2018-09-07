/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 21:05:26 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/07 19:45:32 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		check_color(int pos, t_player *players, WINDOW *win)
{
	int		i;
	int		st;
	int		len;

	i = -1;
	while (++i < g_game.players)
	{
		st = players[i].start;
		len = players[i].len;
		if (pos == st)
		{
			wattron(win, A_REVERSE | A_BLINK);
			wattron(win, COLOR_PAIR(i + 1));
		}
		else if (pos == st + len + 1)
			unset_colors(win);
	}
}

void		write_value(int pl, unsigned char val, int pos, WINDOW *win)
{
	int		x;
	int		y;
	char	*buff;

	y = pos / 64 + 2;
	x = (pos % 64) * 3 + 2;
	wattron(win, COLOR_PAIR(pl));
	mvwprintw(win, y, x, (buff = ft_itoa_base_mod(val, 16, 2)));
	wattroff(win, A_REVERSE | A_BLINK);
	pos % 64 == 63 ? mvwprintw(win, y + 1, 2, "") : wprintw(win, " ");
	ft_strdel(&buff);
}

void		unset_colors(WINDOW *win)
{
	int		i;

	i = -1;
	while (++i < 5)
		wattroff(win, COLOR_PAIR(i));
	wattron(win, COLOR_PAIR(5));
}

void		make_pause(void)
{
	int    	x;
	int    	y;

	y = 2;
	x = 64 * 3 + 7;
	unset_colors(g_game.win);	
	draw_info(g_game.win, &y);
	mvwprintw(g_game.win, (y = 2), x, "** PAUSED ** ");
	draw_frame(g_game.win);
	wrefresh(g_game.win);
	while (true)
		if (getch() == 32)
			break ;
	mvwprintw(g_game.win, y, x, "** RUNNING **");
	wrefresh(g_game.win);
}

void		handle_keys(void)
{
	int 	res;

	res = getch();
	if (res == 27)
	{
		system("pkill afplay");
		system("reset");
		exit(0);
	}
	else if ((res == 32 || g_game.cycle == 1) && g_game.visu)
	{
		system("pkill afplay");
		system("afplay /Users/ydeineha/corwar_fin/visu/audio/matrix.wav &");
		make_pause();
		system("pkill afplay");
		system("afplay /Users/ydeineha/corwar_fin/visu/audio/fight.mp3 &");
	}
	else if (res == 'e' && g_game.timeout > 99)
		g_game.timeout -= 100;
	else if (res == 'r' && g_game.timeout > 499)
		g_game.timeout -= 500;
	else if (res == 'w' && g_game.timeout < 14901)
		g_game.timeout += 100;
	else if (res == 'q' && g_game.timeout < 14501)
		g_game.timeout += 500;
}