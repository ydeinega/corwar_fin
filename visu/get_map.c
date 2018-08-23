#include "corewar.h"

unsigned char		*get_map(t_player **pl)
{
	unsigned char	*map;
	int				i;

	i = -1;
	if (!(map = (unsigned char *)ft_strnew(MAP_SIZE)))
		return (NULL);
	while (pl[++i])
		ft_memmove(map + pl[i]->start, pl[i]->comms);
	return (map);
}
