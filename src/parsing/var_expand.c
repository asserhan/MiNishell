/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otait-ta <otait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:47:06 by otait-ta          #+#    #+#             */
/*   Updated: 2023/05/04 12:47:59 by otait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *subtoken(char *str, int i, t_exec_context *exContext)
{
	char *var_value;
	char *result;
	char *sub;
	int var_len;
	int start;
	int d_quote;
	start = i;
	var_value = NULL;
	if (str[i + 1] == '{')
	{
		var_len = find_char_index(&str[i + 1], "}") - 1;
		if (var_len > 0)
		{
			sub = ft_substr(&str[i + 2], 0, var_len);
			var_value = get_env_value(sub, exContext);
			free(sub);
		}
		i += var_len + 3;
	}
	else
	{
		var_len = find_char_index(&str[i + 1], "|\"' $?><");
		if (var_len == -1)
			var_len = ft_strlen(&str[i + 1]);
		sub = ft_substr(&str[i + 1], 0, var_len);
		var_value = get_env_value(sub, exContext);
		free(sub);
		i += var_len + 1;
	}
	if (!var_value)
	{
		if (str[i - var_len - 1] == '$')
			var_value = ft_strdup("handle the PID");
		else if (str[i - var_len - 1] == '?')
			var_value = ft_strdup("handle the exit status");
		else
			var_value = ft_strdup("");
	}
	d_quote = 0;
	while (str[start - 1 - d_quote] == '"' && str[i + d_quote] == '"')
		d_quote++;
	sub = ft_substr(str, 0, start - d_quote);
	result = ft_strjoin(sub, var_value);
	free(sub);
	free(var_value);
	if (str[i] != '\0')
		result = ft_strjoin(result, &str[i + d_quote]);
	free(str);
	return (result);
}

char *var_expand(char *token, t_exec_context *exContext)
{
	int s_quote;
	int d_quote;
	int i;
	int should_expand;
	char *test;

	s_quote = 0;
	d_quote = 0;
	i = -1;
	while (token[++i])
	{
		handle_quotes(&s_quote, &d_quote, token[i]);
		if (!s_quote && token[i] == '$' && token[i + 1])
		{
			should_expand = 1;
			if (i == 0 || token[i - 1] != '\\')
			{
				if (ft_strchr("/~%^}:; ", token[i + 1]) || (find_char_index("\"", &token[i + 1]) < 0 && d_quote))
					should_expand = 0;
			}
			if (should_expand)
			{
				test = subtoken(token, i, exContext);
				return (var_expand(test, exContext));
			}
		}
	}
	return (token);
}