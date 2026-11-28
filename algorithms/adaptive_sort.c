/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptative_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 10:19:28 by marvin            #+#    #+#             */
/*   Updated: 2026/11/28 10:19:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adaptive_sort(t_stack **stack_a, t_stack **stack_b)
{
	double	disorder;

	disorder = compute_disorder(*stack_a);
	if (disorder == 0.0)
		return ;
	else if (disorder < 0.2)
		sort_simple(stack_a, stack_b);
	else if (disorder < 0.5)
		sort_medium(stack_a, stack_b);
	else
		sort_radix(stack_a, stack_b);
}
