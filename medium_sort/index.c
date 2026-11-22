/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 10:20:22 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/22 10:51:19 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Ordena un array temporal de enteros de menor a mayor
void	bubble_sort_array(int *arr, int size)
{
	int	aux;
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size -1)
		{
			if (arr[j] > arr[j + 1])
			{
				aux = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = aux;
			}
			j++;
		}
		i++;
	}
}

static void	assign_index(t_stack *stack_a, int *nums, int size)
{
	int		i;
	t_stack	*curr;

	curr = stack_a;
	while (curr)
	{
		i = 0;
		while (i < size)
		{
			if (nums[i] == curr->value)
				curr->index = i;
			i++;
		}
		curr = curr->next;
	}
}

//Pide memoria para el array temporal, copia los valores actuales de A, 
//llama a la función de ordenar, y luego recorre tu Stack A reemplazando cada 
//value original por su posición (index) en el array ordenado. Libera el array 
//al terminar.
void	index_stack_a(t_stack *stack_a, int size)
{
	int		*nums;
	int		i;
	t_stack	*curr;

	nums = (int *)malloc(size * sizeof(int));
	if (nums == NULL)
		return ;
	curr = stack_a;
	i = 0;
	while (curr)
	{
		nums[i] = curr->value;
		curr = curr->next;
		i++;
	}
	bubble_sort_array(nums, size);
	assign_index(stack_a, nums, size);
	free(nums);
}
