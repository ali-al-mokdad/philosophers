/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:15:00 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/05/21 16:15:00 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
