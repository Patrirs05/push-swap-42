/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:09:49 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/20 18:09:50 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

struct s_node	*ft_new_node(int n)
{
	struct s_node	*node;

	node = malloc(sizeof(struct s_node));
	if (!node)
		return (NULL);
	node->value = n;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_back(struct s_node **stack, struct s_node *new)
{
	struct s_node	*last;

	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	free_stack(struct s_node **stack)
{
	struct s_node	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
