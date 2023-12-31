/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:32:00 by otait-ta          #+#    #+#             */
/*   Updated: 2023/06/14 21:48:17 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_exec_context	exContext;
	t_doubly_lst	*head;

	input = NULL;
	if (init_data(&exContext, av, env))
		exit(1);
	//rl_catch_signals = 0;
	while (ac)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		if (input)
			free(input);
		input = readline("minishell $ ");
		if (input && !*input)
			continue ;
		if (!input)
		{
			ft_printf("exit\n");
			exit(g_exit_status);
		}
		if (input[0] != '\0')
			add_history(input);
		if (pars_input(&exContext, input))
		{
			//d_lstclear(&exContext.cmds);
			continue ;
		}
		head = exContext.cmds;
		execution(&exContext);
		d_lstclear(&head);
		ft_close_fd(&exContext);
	}
	free_env(&(exContext.env));
	return (0);
}
