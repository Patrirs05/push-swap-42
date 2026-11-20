/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:10:13 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/20 18:10:14 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(struct s_node **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void	sb(struct s_node **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

void	ss(struct s_node **a, struct s_node **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}

void	pa(struct s_node **a, struct s_node **b)
{
	push(b, a);
	write(1, "pa\n", 3);
}

void	pb(struct s_node **a, struct s_node **b)
{
	push(a, b);
	write(1, "pb\n", 3);
}
