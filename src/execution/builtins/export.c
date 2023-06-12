/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otait-ta <otait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:07:12 by hasserao          #+#    #+#             */
/*   Updated: 2023/06/12 22:42:18 by otait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_export(t_env *env)
{
	t_env_variable	*tmp;

	sort_env_var(env->first);
	tmp = env->first;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->content[0] != '\0')
		{
			ft_putstr_fd("=", 1);
			ft_printf("\"%s\"", tmp->content);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

int	_export_parse(char *arg)
{
	int		j;
	char	*alpha;

	alpha = ft_alpha();
	if (start_with(arg, alpha) == 0)
	{
		if (start_with(arg, "-"))
			put_error_ex("export: ", arg, ": export with no option\n", 1);
		else
			put_error_ex("minishell:  export: ", arg,
					": not a valid identifier\n", 1);
		return (1);
	}
	j = 1;
	while (arg[j] && arg[j] != '=')
	{
		if (arg[j] == '+' && arg[j + 1] == '=')
			return (0);
		if (!ft_isdigit(arg[j]) && !ft_isalpha(arg[j]) && arg[j] != '_')
		{
			put_error_ex("minishell:  export: ", arg,
					": not a valid identifier\n", 1);
			return (1);
		}
		j++;
	}
	return (0);
}
char	*ft_elimine_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str));
	if (!new)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			str++;
		new[i++] = *str++;
		;
	}
	new[i] = '\0';
	return (new);
}
void	_export_variable(char *arg, t_env *env)
{
	t_env_variable	*tmp;
	char			*var;
	char			*str;
	char			*s;
	int				i;

	var = arg;
	i = 0;
	while (arg[i] && var[i] != '=' && var[i] != '+')
		i++;
	if (var[i] == '+')
	{
		s = ft_substr(var, 0, i);
		var = ft_elimine_char(var, '+');
		str = ft_substr(var, i + 1, ft_strlen(var));
		tmp = search_env_elem(env, s);
		if (!tmp)
			tmp = create_env_elem(var);
		else
		{
			s = ft_strjoin(s, "=");
			s = ft_strjoin(s, tmp->content);
			s = ft_strjoin(s, str);
			delete_env_elem(env, tmp);
			tmp = create_env_elem(s);
		}
		set_env_elem(env, tmp);
		(free(s), free(str), free(var));
	}
	else
	{
		s = ft_substr(var, 0, i);
		tmp = search_env_elem(env, s);
		if (tmp != NULL)
			delete_env_elem(env, tmp);
		tmp = create_env_elem(arg);
		set_env_elem(env, tmp);
		free(s);
	}
}

void	ft_export(t_exec_context *exContext)
{
	t_env	*copy;
	int		i;

	if (count_matrix(exContext->cmds->args) > 1)
	{
		i = 1;
		while (exContext->cmds->args[i])
		{
			if (!_export_parse(exContext->cmds->args[i]))
				_export_variable(exContext->cmds->args[i], exContext->env);
			else
				return ;
			i++;
		}
	}
	else
	{
		copy = copy_env_list(exContext);
		print_export(copy);
		free_env(&copy);
	}
}
