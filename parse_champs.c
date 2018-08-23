/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:14:05 by ydeineha          #+#    #+#             */
/*   Updated: 2018/07/04 14:14:07 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	parse_champs(void)
{
	t_lst_champs	*tmp;

	tmp = g_game.champ;
	while (tmp)
	{
		if ((tmp->fd = open(tmp->file_name, O_RDONLY)) == -1)
		{
			tmp->error = 12;
			error(12);
		}
		read_champs_info(tmp);
		tmp = tmp->next;
	}
}

unsigned int	read_num(t_lst_champs *champ, int len)
{
	int				ret;
	unsigned char	line[len];

	ret = read(champ->fd, line, len);
	if (ret == -1)
	{
		champ->error = 12;
		error(12);
	}
	if (ret < len)
	{
		champ->error = 11;
		error(11);
	}
	return (conv_hex(line, len));
}

void	read_string(t_lst_champs *champ, char *line, int len)
{
	int		ret;

	ret = read(champ->fd, line, len);
	if (ret == -1)
	{
		champ->error = 12;
		error(12);
	}
	if (ret < len)
	{
		champ->error = 11;
		error(11);
	}
	line[len] = '\0';
}

void	read_instructions(t_lst_champs *champ)
{
	int		ret;
	char	line;

	ret = 0;
	champ->comms = (unsigned char *)malloc(sizeof(unsigned char) * champ->size);
	ret = read(champ->fd, champ->comms, champ->size);
	if (ret == -1)
	{
		champ->error = 12;
		error(12);
	}
	if ((unsigned int)ret < champ->size)
	{
		champ->error = 13;
		error(13);
	}
	ret = read(champ->fd, &line, 1);
	if (ret != 0)
	{
		champ->error = 13;
		error(13);
	}
}

void	read_champs_info(t_lst_champs *champ)
{
	champ->magic = read_num(champ, 4);
	if (champ->magic != COREWAR_EXEC_MAGIC)
	{
		champ->error = 10;
		error(10);
	}
	read_string(champ, champ->name, PROG_NAME_LENGTH);
	if (read_num(champ, 4) != 0)//обычный корвар не распознает эту ошибку
	{
		champ->error = 15;//нужно другую ошибку здесь прописать
		error(15);
	}
	champ->size = read_num(champ, 4);
	if (champ->size > CHAMP_MAX_SIZE)
	{
		champ->error = 14;
		error(14);
	}
	read_string(champ, champ->comment, COMMENT_LENGTH);
	if (read_num(champ, 4) != 0)//обычный корвар не распознает эту ошибку
	{
		champ->error = 15;//has a name/comment which is too long
		error(15);
	}
	read_instructions(champ);
	//print_champ(champ);//del
}
