/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 21:05:26 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/06 21:05:32 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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