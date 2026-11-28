/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 16:04:45 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/22 19:33:51 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Algoritmo complejo: Radix Sort LSD

//Si tienes 100 números, el índice más grande es el 99. En binario, el 99
//se escribe 1100011 (necesita 7 bits). Esta función calcula cuántas pasadas
//de bits tendremos que hacer.
int	get_max_bits(t_stack *stack)
{
	t_stack	*curr;
	int		max_index;
	int		max_bits;

	curr = stack;
	max_index = stack_size(curr) - 1;
	max_bits = 0;
	while (max_index > 0)
	{
		max_index = max_index >> 1; // es lo mismo que 99/2
		max_bits++;
	}
	return (max_bits);
}

//ordenar toda una lista de números fijándose únicamente en una columna de dígitos a la vez
//(por ejemplo, solo las unidades, o solo las decenas)
void	radix_sort_pass(t_stack **stack_a, t_stack **stack_b, int bit, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		(*stack_a)->index;
		if(((*stack_a)->index >> bit) & 1 == 0)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
		i++;
	}
	while (*stack_b)
		pa(stack_a, stack_b);
}

void	sort_radix(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	max_bits;
	int	bit;

	size = stack_size(*stack_a);
	index_stack_a(*stack_a, size);
	max_bits = get_max_bits(*stack_a);
	while (bit < max_bits)
	{
		radix_sort_pass(stack_a, stack_b, bit, size);
		bit++;
	}
}
