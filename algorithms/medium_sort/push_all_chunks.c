/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_all_chunks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 10:53:34 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/22 13:24:19 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//na función simple que recibe el número total de elementos y devuelve el 
//tamaño ideal del chunk (por ejemplo, si size == 100, devuelve 18 o 20). 
//Te permite cambiar el tamaño del chunk en un solo sitio para hacer pruebas.
int	get_chunk_size(int size)
{
	int	sqrt;

	sqrt = 1;
	// Bucle para encontrar la raíz cuadrada entera
	while ((sqrt * sqrt) <= size)
		sqrt++;
	// Ajustamos porque se pasa +1 ej: size 100 ahi tendriamos 11 y no 10
	sqrt--;
	
	// Justificación de la optimización:
	// Como dividimos el chunk en dos niveles en B (arriba y abajo usando rb),
	// duplicamos de manera segura el tamaño óptimo de la ventana.
	return (sqrt * 2);
}

//El bucle principal de la primera fase. Controla el contador (count), obtiene 
//el tamaño del chunk y corre un while (*stack_a) que va llamando a las 
//operaciones de empuje y rotación.
void	push_all_chunks(t_stack **stack_a, t_stack **stack_b)
{
	int		count;
	int		chunk_size;

	count = 0;
	chunk_size = get_chunk_size(stack_size(*stack_a));
	while (*stack_a)
	{
		if ((*stack_a)->index <= count)
		{
			pb(stack_a, stack_b);
			count++;
		}
		else if ((*stack_a)->index < count + chunk_size)
		{
			pb(stack_a, stack_b);
			rb(stack_b);
			count++;
		}
		else
		{
			ra(stack_a);
		}
	}
}

//Recorre el Stack B buscando cuál es el nodo que contiene el índice más alto 
//actualmente y devuelve su posición física actual (por ejemplo: posición 0 si 
//está arriba, posición 5 si está en medio)
int	find_max_index_position(t_stack *stack_b)
{
	t_stack	*curr;
	int		max_index;
	int 	max_pos;
	int		current_pos;

	curr = stack_b;
	max_index = -1;
	max_pos = 0;
	current_pos = 0;
	while (curr)
	{
		if (curr->index > max_index)
		{
			max_index = curr->index;
			max_pos = current_pos;
		}
		current_pos++;
		curr = curr->next;
	}
	return (max_pos);
}

//Recibe la posición del número máximo y calcula el tamaño actual del Stack B. 
//Decide qué es más rápido: si la posición está en la mitad superior, ejecuta rb
//en un bucle; si está en la mitad inferior, ejecuta rrb. Se detiene cuando el 
//máximo está en la posición 0.
void	bring_max_to_top(t_stack **stack_b, int max_pos)
{
	int	size;
	int steps;

	size = stack_size(*stack_b);
	steps = size - max_pos;
	if (max_pos <= size / 2)
	{
		while (max_pos > 0)
		{
			rb(stack_b);
			max_pos--;
		}
	}
	else
	{
		while (steps > 0)
		{
			rrb(stack_b);
			steps--;
		}
	}
}

//El bucle principal de la segunda fase. Mientras B tenga elementos: llama a 
//find_max_index_position, luego a bring_max_to_top, y finalmente ejecuta pa.
void	return_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	pos;

	pos = find_max_index_position(stack_b);
	bring_max_to_top(stack_b, pos);
	pa(stack_a, stack_b);
}
