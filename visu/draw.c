/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:23:41 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/08 14:18:07 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void			draw_procs(WINDOW *win, unsigned char *map)
{
	t_process		*curr;

	wattroff(win, A_BOLD);
	curr = g_game.proc;
	while (curr)
	{
		if (curr->live)
		{
			if (curr->prev >= 0 && map[curr->prev % MEM_SIZE])
			{
				wattroff(win, A_REVERSE | A_BLINK);
				write_value(curr->player, map[curr->prev % MEM_SIZE],
						curr->prev % MEM_SIZE, win);
			}
			if (map[curr->pc % MEM_SIZE] > 0)
			{
				wattron(win, A_REVERSE | A_BLINK);
				write_value(curr->player, map[curr->pc % MEM_SIZE],
						curr->pc % MEM_SIZE, win);
				wattroff(win, A_REVERSE | A_BLINK);
			}
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
	handle_changes();
	draw_procs(win, g_game.board);
	unset_colors(win);
	wrefresh(win);
}
