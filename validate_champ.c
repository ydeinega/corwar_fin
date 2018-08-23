/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 16:30:41 by ydeineha          #+#    #+#             */
/*   Updated: 2018/07/02 16:30:43 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			validate_champ(int argc, char **argv, int *i)
{
	int 			num;
	t_lst_champs	*new;

	num = 0;
	new = NULL;
	if (ft_strequ(argv[*i], "-n"))
		num = validate_champ_num(argc, argv, i);
	if (ft_strstr(argv[*i], ".cor"))//здесь не обязательно кор расширение
	{
		new = num > 0 ? new_champ(argv[*i], num, true) :
		new_champ(argv[*i], num, false);
		add_champ(&(g_game.champ), new);
		g_game.players += 1;
		//возможно, здесь нужно валидировать имя программы
		//в хедер файле задефайнены макс размеры програм_нейм, коммента и мэджик намбер ПОТЕСТИТЬ
	}
	else
		error(4);

}

int				validate_champ_num(int argc, char **argv, int *i)
{
	int num;

	num = 0;
	if (*i + 1 == argc)
		error(2);
	else if (*i + 2 >= argc)
	{
		if (validate_num(argv[*i + 1]))
			error(4);
		else
			error(2);
	}
	else
	{
		*i += 2;
		if (validate_num(argv[*i - 1]))
			num = ft_atoi(argv[*i - 1]);
		else	
			error(2);
	}
	!num || num > MAX_PLAYERS ? error(3) : 0;//использую дефайн из op.h
	g_game.champ ? check_double_positions(num) : 0;
	return (num);
}

void			check_positions(void)
{
	int 			i;
	t_lst_champs	*tmp;

	i = 1;
	tmp = NULL;
	sort_champs();
	tmp = g_game.champ;
	if (tmp->next == NULL && tmp->num != 1)
		error(7);
	while (tmp)
	{
		if (tmp->num != i)
			error(7);
		tmp = tmp->next;
		i++;
	}
}

void			sort_champs(void)
{
	t_lst_champs	*tmp;
	t_lst_champs	*prev;
	int				check;

	tmp = g_game.champ;
	prev = NULL;
	check = -1;
	while (check != 0)
	{
		check = 0;
		while (tmp->next)
		{
			if (tmp->num > tmp->next->num)
			{
				tmp = swap_champs(tmp, prev);
				check++;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		tmp = g_game.champ;
		prev = NULL;
	}
}

t_lst_champs	*swap_champs(t_lst_champs *tmp, t_lst_champs *prev)
{
	t_lst_champs	*swap;

	swap = NULL;
	swap = tmp->next;
	tmp->next = swap->next;
	swap->next = tmp;
	tmp = swap;
	if (prev)
		prev->next = swap;
	else
		g_game.champ = swap;
	return (tmp);
}
