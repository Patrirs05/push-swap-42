#include "sawp_libft.h"

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int		is_strategy_flag(char *str, struct s_config *cfg)
{
	if (!ft_strcmp(str, "--simple"))
	{	
		cfg->strategy = 1;
		return (1);
	}
	if (!ft_strcmp(str, "--medium"))
	{
		cfg->strategy = 2;
		return (1);
	}
	if (!ft_strcmp(str, "--complex"))
	{
		cfg->strategy = 3;
		return (1);
	}
	if (!ft_strcmp(str, "--adaptive"))
	{
		cfg->strategy = 0;
		return (1);
	}
	return (0);
}

int		is_flag(char *str, struct s_config *cfg)
{
	if (is_strategy_flag(str, cfg))
		return (1);
	if (!ft_strcmp(str, "--bench"))
	{
		cfg->bench = 1;
		return (1);
	}
	return (0);
}

