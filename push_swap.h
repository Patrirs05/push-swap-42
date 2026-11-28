/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrirod <patrirod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:09:07 by patrirod          #+#    #+#             */
/*   Updated: 2026/11/22 16:10:28 by patrirod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_stack;

struct s_config
{
	int		strategy;
	int		bench;
};

//parse(correcciòn de errores)
int				is_valid_number(char *str);
long long		ft_atoi_safe(char *str, int *error);
int				duplicate(struct s_node *stack, int n);
int				add_number(struct s_node **stack, char *str);
//a y b
struct s_node	*parse_args(int argc, char **argv);
//stack
struct s_node	*ft_new_node(int n);
void			add_back(struct s_node **stack, struct s_node *new);
void			free_stack(struct s_node **stack);
////utils_base (swap, push, rotate, revers_rotate)
void			swap(struct s_node **stack);
void			push(struct s_node **from, struct s_node **to);
void			rotate(struct s_node **stack);
void			revers_rotate(struct s_node **stack);
//utils_s_p
void			sa(struct s_node **a);
void			sb(struct s_node **b);
void			ss(struct s_node **a, struct s_node **b);
void			pa(struct s_node **a, struct s_node **b);
void			pb(struct s_node **a, struct s_node **b);
//utils_rotate
void			ra(struct s_node **a);
void			rb(struct s_node **b);
void			rr(struct s_node **a, struct s_node **b);
//utils_revers
void			rra(struct s_node **a);
void			rrb(struct s_node **b);
void			rrr(struct s_node **a, struct s_node **b);
//flags
int				ft_strcmp(char *s1, char *s2);
int				is_strategy_flag(char *str, struct s_config *cfg);
int				is_flag(char *str, struct s_config *cfg);
//base_alg
int				stack_size(struct s_node *stack);
int				find_min_pos(struct s_node *stack);
//simple_alg
void			bring_to_top(struct s_node **a, int pos);
void			selection_sort(struct s_node **a, struct s_node **b);
//medium_alg
void			bubble_sort_array(int *arr, int size);
void			index_stack_a(t_stack *stack_a, int size);
int				get_chunk_size(int size);
void			push_all_chunks(t_stack **stack_a, t_stack **stack_b);
int				find_max_index_position(t_stack *stack_b);
void			bring_max_to_top(t_stack **stack_b, int max_pos);
void			return_to_a(t_stack **stack_a, t_stack **stack_b);
void			sort_with_chunks(t_stack **stack_a, t_stack **stack_b);
//complex_alg
int				get_max_bits(t_stack *stack);
void			radix_sort_pass(t_stack **stack_a,
					t_stack **stack_b, int bit, int size);
void			sort_radix(t_stack **stack_a, t_stack **stack_b);
//adaptive_alg
double			compute_disorder(struct s_node *a);
void			adaptive_sort(t_stack **stack_a, t_stack **stack_b);

#endif