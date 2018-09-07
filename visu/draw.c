/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:23:41 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/07 19:38:14 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		write_val(unsigned char val, int pos, WINDOW *win)
{
	int		x;
	int		y;
	char	*buff;

	y = pos / 64 + 2;
	x = (pos % 64) * 3 + 2;
	mvwprintw(win, y, x, (buff = ft_itoa_base_mod(val, 16, 2)));
	wattroff(win, A_REVERSE | A_BLINK);
	ft_strdel(&buff);
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
		if (curr->live)
		{
			if (curr->prev >= 0)
			{
				wattroff(win, A_REVERSE | A_BLINK);
				write_val(map[curr->prev % MEM_SIZE],
						curr->prev % MEM_SIZE, win);			
			}
			wattron(win, COLOR_PAIR(curr->player));
			wattron(win, A_REVERSE | A_BLINK);
			write_val(map[curr->pc % MEM_SIZE],
					curr->pc % MEM_SIZE, win);
			wattroff(win, A_REVERSE | A_BLINK);
		}
		curr = curr->next;
	}
}

void				draw_all(WINDOW *win)
{
	int				y;

	y = 2;
	unset_colors(win);
	draw_frame(win);
	draw_info(win, &y);
	// handle_changes();
	draw_procs(win);
	unset_colors(win);
	wrefresh(win);
}
