#include "sawp_libft.h"

double	compute_disorder(struct s_node *a)
{
	struct s_node	*i;
	struct s_node	*j;
	size_t			mistakes;
	size_t			total_pairs;

	mistakes = 0;
	total_pairs = 0;
	i = a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0)
		return (0.0);
	return ((double)mistakes / (double)total_pairs);
}
