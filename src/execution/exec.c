/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:48:35 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/27 00:16:48 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

void	exec_builtins(t_exec_context *exContext)
{
	// pid_t	pid;
	// char	*str[4];

	// str[4] = {"ls", "-l", NULL};
	if (ft_strcmp(exContext->cmds->cmd, "env") == 0)
		ft_env(exContext);
	if (ft_strcmp(exContext->cmds->cmd, "export") == 0)
		ft_export(exContext);
	if (ft_strcmp(exContext->cmds->cmd, "echo") == 0)
		ft_echo(exContext->cmds->args);
	if (ft_strcmp(exContext->cmds->cmd, "unset") == 0)
		ft_unset(exContext);
	if (ft_strcmp(exContext->cmds->cmd, "cd") == 0)
		ft_cd(exContext->cmds->args, exContext->env);
	if (ft_strcmp(exContext->cmds->cmd, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(exContext->cmds->cmd, "exit") == 0)
		ft_exit(exContext->cmds->args);
	// pid=fork();
	// if (pid == 0)
	// 	execve("/bin/ls", str, NULL);
	// else
	// 	wait(NULL);
	// //execve("/bin/ls", str, NULL);
}
// void execution(t_exec_context *exContext)
// {
// }
