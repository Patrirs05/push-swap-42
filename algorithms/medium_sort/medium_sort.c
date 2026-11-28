/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:11:18 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/22 13:30:06 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Algoritmo intermedio: Orden basado en chunks (dividiendo en √n chunks)
#include "push_swap.h"

void	sort_with_chunks(t_stack **stack_a, t_stack **stack_b)
{
	index_stack_a(stack_a, stack_size(*stack_a));
	push_all_chunks(stack_a, stack_b);
	return_to_a(stack_a, stack_b);
}
