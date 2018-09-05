#include "corewar.h"

static void	clean_champ_lst(void)
{
	t_lst_champs	*tmp;

	tmp = NULL;
	while (g_game.champ)
	{
		tmp = g_game.champ;
		g_game.champ = g_game.champ->next;
		if (tmp->comms)
		{
			free(tmp->comms);
			tmp->comms = NULL;
		}
		free(tmp);
	}
}

static void	clean_player_arr(void)
{
	int i;

	i = 0;
	while (i < g_game.players)
	{
		ft_strdel(&(g_game.player[i].name));
		ft_strdel(&(g_game.player[i].comment));
		free(g_game.player[i].comms);//???
		g_game.player[i].comms = NULL;
		i++;
	}
	free(g_game.player);
	g_game.player = NULL;
}

static void	clean_proc_lst(void)
{
	t_process	*tmp;

	tmp = NULL;
	while (g_game.proc)
	{
		tmp = g_game.proc;
		g_game.proc = g_game.proc->next;
		free(tmp);
	}
}

void		clean_all(void)
{
		if (g_game.champ)
			clean_champ_lst();
		if (g_game.player)
			clean_player_arr();
		if (g_game.board)
		{
			free(g_game.board);
			g_game.board = NULL;
		}
		if (g_game.proc)
			clean_proc_lst();
}