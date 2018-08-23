/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 16:32:55 by ydeineha          #+#    #+#             */
/*   Updated: 2018/07/02 16:32:57 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_lst_champs	*new_champ(char *file_name, int num, bool n_flag)
{
	t_lst_champs	*champ;

	champ = (t_lst_champs *)malloc(sizeof(t_lst_champs));
	if (!champ)
		return (NULL);
	champ->file_name = file_name;
	champ->num = num;
	champ->error = 0;
	champ->n_flag = n_flag;
	champ->fd = 0;
	//champ->file_cont = NULL;
	champ->size = 0;
	champ->magic = 0;
	//champ->name = NULL;
	//champ->comment = NULL;
	champ->comms = NULL;
	champ->next = NULL;
	return (champ);
}

void			add_champ(t_lst_champs **head, t_lst_champs *new)
{
	if (head && new)
	{
		if (*head)
		{
			new->next = *head;
			*head = new;
		}
		else
			*head = new;
	}
}

void			set_blank_positions(void)
{
	t_lst_champs		*tmp;
	int					num;

	tmp = g_game.champ;
	num = g_game.players;
	while (tmp)
	{
		if (tmp->n_flag == false)
		{
			champ_position(tmp, num);//op.h
			num = tmp->num - 1;
		}
		tmp = tmp->next;
	}
}

//Все еще вопрос, как нумеровать чемпионов??? от 1 до 4 или от 4 до 1-го???
void	champ_position(t_lst_champs *champ, int num)
{
	t_lst_champs	*tmp;
	int				check;

	check = 0;
	tmp = g_game.champ;
	while (tmp)
	{
		if (tmp->num == num)
		{
			check++;
			num--;
		}
		tmp = !check ? tmp->next : g_game.champ;
		check = 0;
	}
	champ->num = num;
}

void	check_double_positions(int num)
{
	t_lst_champs	*tmp;

	tmp = g_game.champ;
	while (tmp)
	{
		if (tmp->num == num && tmp->n_flag == true)
			error(5);
		tmp = tmp->next;
	}
}
