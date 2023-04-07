/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otait-ta <otait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:32:00 by otait-ta          #+#    #+#             */
/*   Updated: 2023/04/07 21:35:46 by otait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char const **av, char **env)
{
	t_exec_context	exContext;
	char			*input;

	(void)ac;
	(void)av;
	(void)env;
	if (init_data(&exContext, (char **)av, env))
		exit(1);
	while (1)
	{
		input = readline("minishell $ ");
		// / pars_input();
	}
	return (0);
}
