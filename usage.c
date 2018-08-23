/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 15:06:13 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/30 15:06:15 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	char	*g_usage[19] =
**	{
**	0	"Usage: ./corewar",
**	1	"-n number",
**	2	"Sets the number of the next player",
**	3	"-a",
**	4	"Prints output from "aff" (Default is to hide it)",
**	5	"#### TEXT OUTPUT MODE "
**		"##########################################################",
**	6	"-dump nbr_cycles",
**	7	"Dumps memory after nbr_cycles and exits",
**	8	"-v number",
**	9	"Verbosity levels, can be added together to enable several",
**	10	"- 0 : Show only essentials",
**	11	"- 1 : Show lives",
**	12	"- 2 : Show cycles",
**	13	"- 4 : Show operations (Params are NOT litteral ...)",
**	14	"- 8 : Show deaths",
**	15	"-16 : Show PC movements (Except for jumps)",
**	16	"#### NCURSES OUTPUT MODE "
**		"#######################################################",
**	17	"-visu nbr_cycles",
**	18	"Runs nbr_cycles and then starts ncurses output mode"
**	}
*/

/*
**	char	*g_error[16] =
**	{
**	0		"invalid argument",
** 	1		"argument nbr_cycles is invalid or missing\n"
**			"Nbr_cycles argument is needed after -dump",
**	2		"argument number is invalid or missing\n"
**			"Number argument is needed after -n",
**	3		"number argument (after -v) must be in the range from 1 to (MAX_PLAYERS)",
**	4		"champion is missing",
**	5		"champions cannot have same numbers",
**	6		"too many players. Max number of champions is (MAX_PLAYERS)",
**	7		"numbering value inconsistent"
**	8		"argument number is invalid or missing\n"
**			"Number argument is needed after -v",
**	9		"number argument (after -v) must be in the range from 0 to 31",
**	10		"has an invalid header",
**	11		"is too small to be a champion",
**	12		"cannot be opened and/or read",
**	13		"has a code size that differs from what its header says",
**	14		"is too big to be a champion",
**	15		"has a name/comment which is too long"
**	};
*/

char	*g_usage[19] =
{
	"Usage: ./corewar",
	"-n number",
	"Sets the number of the next player",
	"-a",
	"Prints output from \"aff\" (Default is to hide it)",
	"#### TEXT OUTPUT MODE "
	"###############################################################",
	"-dump nbr_cycles",
	"Dumps memory after nbr_cycles and exits",
	"-v number",
	"Verbosity levels, can be added together to enable several",
	"- 0 : Show only essentials",
	"- 1 : Show lives",
	"- 2 : Show cycles",
	"- 4 : Show operations (Params are NOT litteral ...)",
	"- 8 : Show deaths",
	"-16 : Show PC movements (Except for jumps)",
	"#### NCURSES OUTPUT MODE "
	"############################################################",
	"-visu nbr_cycles",
	"Runs nbr_cycles and then starts ncurses output mode"
};

char	*g_error[16] =
{
	"invalid argument",
	"argument nbr_cycles is invalid or missing\n"
	"Nbr_cycles argument is needed after -dump",
	"argument number is invalid or missing\n"
	"Number argument is needed after -n",
	"number argument (after -n) must be in the range from 1 to ",
	"champion is missing",
	"champions cannot have same numbers",
	"too many players. Max number of champions is ",
	"numbering value inconsistent",
	"argument number is invalid or missing\n"
	"Number argument is needed after -v",
	"number argument (after -v) must be in the range from 0 to 31",
	"has an invalid header",
	"is too small to be a champion",
	"cannot be opened and/or read",
	"has a code size that differs from what its header says",
	"is too big to be a champion",
	"has a name/comment which is too long"
};

void	usage(void)
{
	ft_printf("%s [%s %s | %s] [%s] [[%s] champion1.cor] ...\n", g_usage[0],
		g_usage[6], g_usage[8], g_usage[17], g_usage[3], g_usage[1]);
	ft_printf("%5c%-20s: %s\n", ' ', g_usage[3], g_usage[4]);
	ft_printf("%5c%-20s: %s\n", ' ', g_usage[1], g_usage[2]);
	ft_printf("%s\n", g_usage[5]);
	ft_printf("%5c%-20s: %s\n", ' ', g_usage[6], g_usage[7]);
	ft_printf("%5c%-20s: %s\n", ' ', g_usage[8], g_usage[9]);
	ft_printf("%27c%s\n%27c%s\n%27c%s\n%27c%s\n%27c%s\n%27c%s\n",
		' ', g_usage[10], ' ', g_usage[11], ' ', g_usage[12],
		' ', g_usage[13], ' ', g_usage[14], ' ', g_usage[15]);
	ft_printf("%s\n", g_usage[16]);
	ft_printf("%5c%-20s: %s\n", ' ', g_usage[17], g_usage[18]);
	exit(1);
}

void	error(int num)
{
	t_lst_champs	*tmp;

	tmp = NULL;
	if (num >= 0)
	{
		ft_printf("ERROR: ");
		if (num >= 10 && num <= 15)
		{
			tmp = g_game.champ;
			while (tmp)
			{
				if (tmp->error == num)
					ft_printf("File %s ", tmp->file_name);
				tmp = tmp->next;
			}
		}
		ft_printf("%s", g_error[num]);
		if (num == 6 || num == 3)
			ft_printf("%d", MAX_PLAYERS);
		ft_printf("\n");
	}
	//clean_game
	exit(1);
}
