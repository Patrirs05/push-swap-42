#include "sawp_libft.h"

//Algoritmo sencillo: Adaptación del orden por selección

int	 stack_size(struct s_node *stack)
{
	int		size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

// Búsqueda del mínimo (find_min_pos): Recorre toda la pila a para 
// encontrar la posición del número más pequeño que queda sin ordenar.
int		find_min_pos (struct s_node *stack)
{
	int		min;
	int		pos;
	int		min_pos;

	if (!stack)
		return (-1);
	min = stack->value;
	pos = 0;
	min_pos = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_pos = pos;
		}
		pos++;
		stack = stack->next;
	}
	return (min_pos);
}

// Extracción a la otra pila (bring_to_top + pb): Lleva ese mínimo 
// a la cima usando el camino más corto (ra si está en la mitad 
// superior, rra si está en la inferior) y lo pasa a la pila b.
void	bring_to_top(struct s_node **a, int pos)
{
	int		size;

	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos > 0)
		{
			ra(a);
			pos--;
		}
	}
	else
	{
		pos = size - pos;
		while (pos > 0)
		{
			rra(a);
			pos--;
		}
	}
}

void	selection_sort(struct s_node **a, struct s_node **b)
{
	while (*a)
	{
		bring_to_top(a, find_min_pos(*a));
		pb(a, b);
	}
	// Reconstrucción ordenada (pa): Al repetir esto hasta vaciar a, 
	// los números quedan apilados en b de mayor a menor (el más 
	// grande arriba). Al devolverlos todos a a con pa, quedan ordenados 
	// de menor a mayor.
	while (*b)
		pa(a, b);
}
