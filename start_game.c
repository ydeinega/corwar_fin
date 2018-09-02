#include "corewar.h"

t_player		*create_players(void)
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
		player[i].num = i + 1;
		player[i].name = tmp->name;
		player[i].comment = tmp->comment;
		player[i].comms = tmp->comms;
		player[i].len = tmp->size;
		player[i].start = (MEM_SIZE / g_game.players) * i;
		player[i].last_live = 0;
		player[i].lives_in_curr = 0;
		player[i].lives_in_curr_all = 0;
		g_game.champ = g_game.champ->next;
		free(tmp);
	}
	return (player);
}

unsigned char	*create_board(t_player *player)
{
	unsigned char	*board;
	int				i;

	i = -1;
	if (!(board = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
	{
		perror("malloc() in create_board() failed ");
		error(-1);
	}
	board = ft_memset(board, 0, MEM_SIZE);
	while (++i < g_game.players)
		ft_memcpy(&board[player[i].start], player[i].comms, player[i].len);
	return (board);
}

void			dump(void)
{
	int				i;

	i = 0;
	//DEL
	ft_printf("Introducing contestants...\n");
	ft_printf("* Player 1, weighing 45 bytes, \"salamahenagalabadoun\" (\"sussKBO hin hin\") !\n");
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)//change it to 32 (in subject it is 32 bytes)
		{
			if (i != 0)
				ft_printf("\n");
			if (i == 0)
				ft_printf("0x0000 : ");
			else
				ft_printf("%#06x : ", i);
		}
		ft_printf("%02x ", g_game.board[i]);
		i++;
	}
	ft_printf("\n");
}

void			start_game(void)
{
	g_game.player = create_players();
	//del
	//ft_printf("%s\n", g_game.player[0].name);
	g_game.board = create_board(g_game.player);
	g_game.proc = create_process(g_game.player);
	if (g_game.visu)
		g_game.win = visual_init();
	//print_proc(g_game.proc);//
	run_game();
	
	//dump();
	//free(player);
	//free(board);
}