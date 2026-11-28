/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:10:26 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/20 18:10:27 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_number(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	overflow(long long res, int sign)
{
	if (sign == 1 && res > 2147483647)
		return (1);
	if (sign == -1 && res > 2147483648)
		return (1);
	return (0);
}

long long	ft_atoi_safe(char *str, int *error)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	*error = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		res = (res * 10) + (str[i] - '0');
		if (overflow(res, sign))
		{
			*error = 1;
			return (0);
		}
		i++;
	}
	return (res * sign);
}

int	duplicate(struct s_node *stack, int n)
{
	while (stack)
	{
		if (stack->value == n)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int	add_number(struct s_node **stack, char *str)
{
	long long		n;
	int				error;
	struct s_node	*node;

	if (!is_valid_number(str))
		return (0);
	n = ft_atoi_safe(str, &error);
	if (error || duplicate(*stack, (int)n))
		return (0);
	node = ft_new_node((int)n);
	if (!node)
		return (0);
	add_back(stack, node);
	return (1);
}
