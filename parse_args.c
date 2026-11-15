#include "sawp_libft.h"

struct s_node	*parse_args(int argc, char **argv, struct s_config *cfg)
{
	struct s_node	*stack;
	int				i;

	stack = NULL;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i], cfg))
		{
			if (!add_number(&stack, argv[i]))
			{
				free_stack(&stack);
				write(2, "Error\n", 6);
				return (NULL);
			}
		}
		i++;
	}
	return (stack);
}

/*struct s_node	*parse_args(int argc, char **argv)
{
	struct s_node	*stack;
	int				i;

	stack = NULL;
	i = 1;
	while (i < argc)
	{
		if (!add_number(&stack, argv[i]))
		{
			free_stack(&stack);
			write(2, "Error\n", 6);
			return (NULL);
		}
		i++;
	}
	return (stack);
}*/
