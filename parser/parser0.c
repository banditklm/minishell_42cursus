/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:52:19 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 13:36:12 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	token_handler(t_minishell *minishell)
{
	get_del(minishell);
	expainding(minishell);
	qexp_handler(minishell);
	wildcard(minishell);
	card_to_text(minishell);
	exp_blank(minishell);
	rm_exp(minishell);
	stick_tok(minishell);
	rm_blank(minishell);
	q_to_text(minishell);
	fill_cmd(minishell);
	token_cmd(minishell);
	token_index(minishell);
}

static bool	helper_syntx(t_minishell *msh, char *line, int index)
{
	bool	b;

	open_heredocs(msh, line, index);
	b = true;
	ft_exit_status(1, SET);
	return (b);
}

bool	syntax_errorb(t_minishell *minishell, char *line, int index)
{
	bool	b;
	char	*error;
	char	var[2];

	if (!minishell->sflag)
	{
		if (line[index] == '\0')
			ft_putstr_fd("minishell: syntax error near \
unexpected token `newline'\n", 2);
		else
		{
			(1) && (var[0] = line[index], var[1] = '\0');
			error = ft_strjoin(minishell, "minishell: syntax error \
near unexpected token `", var);
			error = ft_strjoin(minishell, error, "'\n");
			ft_putstr_fd(error, 2);
		}
		b = helper_syntx(minishell, line, index);
	}
	else
		b = helper_syntx(minishell, line, index);
	return (b);
}
