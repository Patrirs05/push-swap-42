#include "sawp_libft.h"

void	swap(struct s_node **stack)
{
	struct s_node	*first;
	struct s_node	*second;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*stack = second;
}

/*void	swap(struct s_node **stack)
{
	struct s_node	*first;
	struct s_node	*second;

	// Si hay 0 o 1 nodos, no se puede intercambiar
	if (!*stack || !(*stack)->next)
		return ;
	// 1. Guardamos los dos primeros nodos
	first = *stack;
	second = first->next;
	// 2. Enganchamos el 1º con el 3º (ida y vuelta)
	first->next = second->next;
	if (first->next)
		first->next->prev = first;
	// 3. Ponemos el 2º como nueva cabeza
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	// 4. Actualizamos la cima de la pila
	*stack = second
}*/

void	push(struct s_node **from, struct s_node **to)
{
	struct s_node	*node;

	if (!*from)
		return ;
	node = *from;
	*from = node->next;
	if (*from)
		(*from)->prev = NULL;
	//node->prev = NULL;
	node->next = *to;
	if (*to)
		(*to)->prev = node;
	*to = node;
}

/*
void	push(struct s_node **from, struct s_node **to)
{
	struct s_node	*node;

	// Si la pila origen está vacía, no hacemos nada
	if (!*from)
		return ;
	// 1. Guardamos el nodo de la cima de 'from'
	node = *from;
	// 2. Avanzamos la cima de 'from' al siguiente nodo
	*from = node->next;
	// 3. Si 'from' no se quedó vacía, cortamos el enlace hacia atrás de la nueva cima
	if (*from)
		(*from)->prev = NULL;
	// (Esta línea sobra porque 'node' ya era la cima y su prev ya era NULL)
	//node->prev = NULL;
	// 4. Enganchamos 'node' por delante de la cima actual de 'to'
	node->next = *to;
	// 5. Si 'to' tenía elementos, enlazamos su antigua cima hacia atrás con 'node'
	if (*to)
		(*to)->prev = node;
	// 6. Actualizamos la nueva cima de 'to'
	*to = node;
}
*/

void	rotate(struct s_node **stack)
{
	struct s_node	*first;
	struct s_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	*stack = first->next;
	(*stack)->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
}

/*void	rotate(struct s_node **stack)
{
	struct s_node	*first;
	struct s_node	*last;

	// Si hay 0 o 1 nodos, rotar no cambia nada
	if (!*stack || !(*stack)->next)
		return ;
	// 1. Guardamos el primer nodo y buscamos el último recorriendo la lista
	first = *stack;
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	// 2. El segundo nodo pasa a ser la nueva cima de la pila
	*stack = first->next;
	(*stack)->prev = NULL;
	// 3. Enganchamos el antiguo primer nodo al final de la lista (ida y vuelta)
	last->next = first;
	first->prev = last;
	first->next = NULL;
}
*/

void	revers_rotate(struct s_node **stack)
{
	struct s_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	last->prev->next = NULL;
	last->prev = NULL;
	last->next = *stack;
	(*stack)->prev = last;
	*stack = last;
}

/*void	revers_rotate(struct s_node **stack)
{
	struct s_node	*last;

	// Si hay 0 o 1 nodos, no se puede rotar
	if (!*stack || !(*stack)->next)
		return ;
	// 1. Buscamos el último nodo de la pila
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	// 2. El penúltimo nodo pasa a ser el nuevo final de la lista
	last->prev->next = NULL;
	// 3. Desconectamos 'last' por detrás y lo enganchamos delante de la antigua cima
	last->prev = NULL;
	last->next = *stack;
	(*stack)->prev = last;
	// 4. Actualizamos 'last' como la nueva cima de la pila
	*stack = last;
}
*/