/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:49:36 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/07 19:39:35 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "../corewar.h"

void			draw_map(WINDOW *win);
void			draw_all(WINDOW *win);
WINDOW			*visual_init(void);
char			*ft_itoa_base_mod(intmax_t nb, int base, int flag);
void			draw_info(WINDOW *win, int *y);
void			draw_breakdowns(WINDOW *win, int *y, int x);
void			handle_changes(void);
void			write_value(int pl, unsigned char val, int pos, WINDOW *win);
void			unset_colors(WINDOW *win);
void			draw_frame(WINDOW *win);
void			check_color(int pos, t_player *players, WINDOW *win);
void			make_pause(void);
void			handle_keys(void);

#endif
