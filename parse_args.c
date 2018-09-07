/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 15:03:34 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/30 15:03:38 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	validate_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (!check_if_int(str))
		return (false);
	return (true);
}

bool	check_if_int(char *str)
{
	char	*s;
	int		len;
	int		i;

	i = -1;
	s = "2147483647";
	len = ft_strlen(str);
	if (len < 10 || len > 10)
		return (len < 10);
	else if (len == 10)
	{
		while (str[++i])
		{
			if (str[i] < s[i])
				return (true);
			if (str[i] > s[i])
				return (false);
		}
	}
	return (1);
}

void	validate_dump(int argc, char **argv, int *i)
{
	if (g_game.dump == true)
		error(0);
	if (*i + 1 == argc)
		error(1);
	g_game.dump = true;
	*i += 1;
	if (!validate_num(argv[*i]))
		error(1);
	g_game.nbr_cycles = ft_atoi(argv[*i]);
}

void	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-dump"))
			validate_dump(argc, argv, &i);
		else if (ft_strequ(argv[i], "-visu"))
			validate_visu(argc, argv, &i);
		else if (ft_strequ(argv[i], "-v"))
			validate_verbal(argc, argv, &i);
		else if (ft_strequ(argv[i], "-a"))
			g_game.a = 1;
		else if (ft_strequ(argv[i], "-n") || ft_strstr(argv[i], ".cor"))
		{
			g_game.players == MAX_PLAYERS ? error(6) : 0;
			validate_champ(argc, argv, &i);
		}
		else
			error(0);
		i++;
	}
	!g_game.players ? error(4) : 0;
	set_blank_positions();
	check_positions();
}
