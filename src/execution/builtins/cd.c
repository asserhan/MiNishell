/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:56:51 by hasserao          #+#    #+#             */
/*   Updated: 2023/05/25 23:45:48 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static char *go_home(t_env *env)
// {
// 	t_env_variable *tmp;
// 	tmp = env->first;
// 	while(tmp)
// 	{
// 		if(ft_strcmp(tmp->name,"HOME") == 0)
// 			return (tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);

// }
static char	*get_env_path(t_env *env, char *name)
{
	t_env_variable	*tmp;

	tmp = env->first;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
static void	update_pwd(t_env *env, char *name)
{
	t_env_variable	*tmp;
	// t_env_variable	*old_pwd;
	char			pwd[PATH_MAX];
	char 			*home;

	tmp = env->first;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->content);
			if (getcwd(pwd, PATH_MAX))
				tmp->content = ft_strdup(pwd);
			else
			{
				if (search_env_elem(env, "OLDPWD"))
					tmp->content = ft_strdup(search_env_elem(env, "OLDPWD")->content);
				else
				{
					home = get_env_path(env, "HOME");
					tmp->content = ft_strdup(home);
				}
					
			}
		}
		tmp = tmp->next;
	}
}
void	ft_cd(char **arg, t_env *env)
{
	char	*path;
	//char	new_path[PATH_MAX];

	if (!arg)
	{
		path = get_env_path(env, "HOME");
		chdir(path);
		// printf ("%s\n", path);
	}
	else
	{
		path = arg[0];
		// new_path = get_env_path(env, "OLDPWD");
		// if (new_path == NULL)
		// {
		// 	put_error_ex("minishell: cd: OLDPWD not set\n", NULL, NULL, 127);
		// 	return ;
		// }
		if (chdir(path) == -1)
		{
			perror("chdir()");
			return ;
		}
		//ft_printf("%s\n", new_path);
		update_pwd(env, "PWD");
		update_pwd(env, "OLDPWD");
	}
}
