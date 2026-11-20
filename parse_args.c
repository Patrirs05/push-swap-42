/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:10:30 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/20 18:10:33 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

struct s_node	*parse_args(int argc, char **argv, struct s_config *cfg)
{
	struct s_node	*stack;
	int				i;

	stack = NULL;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i], cfg))
		{
			if (!add_number(&stack, argv[i]))
			{
				free_stack(&stack);
				write(2, "Error\n", 6);
				return (NULL);
			}
		}
		i++;
	}
	return (stack);
}

/*struct s_node	*parse_args(int argc, char **argv)
{
	struct s_node	*stack;
	int				i;

	stack = NULL;
	i = 1;
	while (i < argc)
	{
		if (!add_number(&stack, argv[i]))
		{
			free_stack(&stack);
			write(2, "Error\n", 6);
			return (NULL);
		}
		i++;
	}
	return (stack);
}*/
