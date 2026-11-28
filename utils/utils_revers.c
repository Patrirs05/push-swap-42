/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_revers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:09:57 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/20 18:10:01 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(struct s_node **a)
{
	revers_rotate(a);
	write(1, "rra\n", 4);
}

void	rrb(struct s_node **b)
{
	revers_rotate(b);
	write(1, "rrb\n", 4);
}

void	rrr(struct s_node **a, struct s_node **b)
{
	revers_rotate(a);
	revers_rotate(b);
	write(1, "rrr\n", 4);
}
