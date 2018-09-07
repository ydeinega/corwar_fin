/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:09 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:32:12 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		add_to_change(t_change *new)
{
	if (new)
	{
		new->next = g_game.change;
		g_game.change = new;
	}
}

static t_change	*new_change(int player, unsigned char *str, int len, int index)
{
	t_change	*new;

	new = (t_change *)malloc(sizeof(t_change));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = str;
	new->len = len;
	new->pos = index;
	new->player = player;
	return (new);
}

void			store_value(t_process *proc, unsigned int value,
							int delta, int base)
{
	int				index;
	unsigned char	*str;
	int				i;
	int				len;

	i = 0;
	str = to_hex_str(value);
	len = 4;
	index = (proc->pc + (delta % base)) % MEM_SIZE;
	if (index < 0)
		index = (MEM_SIZE + index) % MEM_SIZE;
	if (g_game.visu && g_game.change)
		add_to_change(new_change(proc->player, str, len, index));
	else if (g_game.visu)
		g_game.change = new_change(proc->player, str, len, index);
	while (i < len)
	{
		g_game.board[index] = str[i];
		i++;
		index = (index + 1) % MEM_SIZE;
	}
	if (!g_game.visu)
		free(str);
}

unsigned char	*to_hex_str(unsigned int num)
{
	unsigned char		*str;

	if (!(str = (unsigned char *)malloc(sizeof(unsigned char) * 4)))
	{
		perror("malloc() in to_hex_str() failed ");
		error(-1);
	}
	ft_memset(str, 0, 4);
	if (!str)
		return (NULL);
	str[0] = (num & 4278190080) >> 24;
	str[1] = (num & 16711680) >> 16;
	str[2] = (num & 65280) >> 8;
	str[3] = num & 255;
	return (str);
}
