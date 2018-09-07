/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 20:01:08 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/07 20:01:10 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	copy_info(t_player *player, t_lst_champs *tmp, int i)
{
	player[i].num = i + 1;
	player[i].name = ft_strdup(tmp->name);
	player[i].comment = ft_strdup(tmp->comment);
	player[i].comms = tmp->comms;
	player[i].len = tmp->size;
	player[i].start = (MEM_SIZE / g_game.players) * i;
	player[i].last_live = 0;
	player[i].lives_in_curr = 0;
	player[i].lives_in_curr_all = 0;
}

t_player	*create_player_arr(void)
{
	t_player		*player;
	t_lst_champs	*tmp;
	int				i;

	i = -1;
	if (!(player = (t_player *)malloc(sizeof(t_player) * g_game.players)))
	{
		perror("malloc() in create_players() failed ");
		error(-1);
	}
	while (++i < g_game.players)
	{
		tmp = g_game.champ;
		copy_info(player, tmp, i);
		g_game.champ = g_game.champ->next;
		free(tmp);
	}
	return (player);
}
