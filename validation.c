/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:14:32 by ydeineha          #+#    #+#             */
/*   Updated: 2018/07/03 18:14:34 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	validate_visu(int argc, char **argv, int *i)
{
	g_game.visu = true;
	if (*i + 1 < argc && validate_num(argv[*i + 1]))
	{
		*i += 1;
		g_game.nbr_cycles_visu = ft_atoi(argv[*i]);
	}
}

void	validate_verbal(int argc, char **argv, int *i)
{
	int num;

	num = 0;
	if (*i + 1 == argc)
		error(8);
	else
	{
		*i += 1;
		if (validate_num(argv[*i]))
			num = ft_atoi(argv[*i]);
		else	
			error(8);
	}
	num > 31 ? error(9) : 0;
	g_game.v = true;
	g_game.number_v = num;
}
