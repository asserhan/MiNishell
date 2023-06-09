/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otait-ta <otait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:32:00 by otait-ta          #+#    #+#             */
/*   Updated: 2023/06/09 15:10:10 by otait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_exec_context	exContext;

	(void)ac;
	// (void)av;
	// (void)env;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	input = NULL;
	while (1)
	{
		if (input)
			free(input);
		ft_printf("%p \n", input);
		if (init_data(&exContext, av, env))
			exit(1);
		input = readline("minishell $ ");
		if (!input)
			exit(g_exit_status);
		if (input[0] != '\0')
			add_history(input);
		if (pars_input(&exContext, input))
		{
			d_lstclear(&exContext.cmds);
			free_env(&(exContext.env));
			continue ;
		}
		// execution(&exContext);
		d_lstclear(&exContext.cmds);
		free_env(&(exContext.env));
	}
	return (0);
}
