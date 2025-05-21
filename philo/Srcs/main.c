#include "../Include/philosophers.h"

int	main(int ac, char **av)
{
	t_tools			tools;

	parse_arguments(ac, av, &tools);
	setup_tools(&tools);
	ft_philosophers(&tools);
	ft_clean(&tools);
	return (0);
}
