/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 11:38:46 by marvin            #+#    #+#             */
/*   Updated: 2026/11/28 11:38:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	struct s_node	*stack_a;
	struct s_node	*stack_b;
	struct s_config	cfg;

	stack_a = NULL;
	stack_b = NULL;
	cfg.strategy = 0;
	cfg.bench = 0;
	cfg.error = 0;
	if (argc < 2)
		return (0);
	stack_a = parse_args(argc, argv, &cfg);
	if (!stack_a)
		return (cfg.error);
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	sort_stack(&stack_a, &stack_b, &cfg);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
