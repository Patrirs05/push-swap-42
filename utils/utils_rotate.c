/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:10:06 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/20 18:10:07 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(struct s_node **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void	rb(struct s_node **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void	rr(struct s_node **a, struct s_node **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
