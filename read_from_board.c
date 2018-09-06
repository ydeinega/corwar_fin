/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_board.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:04:13 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/06 19:04:16 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*extract_line(int pc, int length)
{
	int				i;
	unsigned char	*line;

	i = 0;
	if (!(line = (unsigned char *)malloc(sizeof(unsigned char) * length)))
	{
		perror("malloc() in extract_line() failed ");
		error(-1);
	}
	while (i < length)
	{
		line[i] = g_game.board[pc];
		i++;
		pc = (pc + 1) % MEM_SIZE;
	}
	return (line);
}

unsigned int	read_from_board(int pc, int length)
{
	unsigned char	*line;
	unsigned int	res;

	line = NULL;
	res = 0;
	line = extract_line(pc, length);
	res = conv_hex(line, length);
	free(line);
	return (res);
}
