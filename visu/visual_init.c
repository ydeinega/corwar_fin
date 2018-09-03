/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 16:57:08 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/07/02 21:25:28 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static WINDOW	*win_create(void)
{
	WINDOW		*win;

	win = newwin(66, 64 * 4, 0, 0);
	// box(win, 0, 0);
	wrefresh(win);
	return (win);
}

WINDOW			*visual_init(void)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	start_color();
	curs_set(0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	return (win_create());
}
