/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:19:16 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/09 00:53:08 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	handel_in0(t_minishell *msh, char *line, t_tokens *tmp_token, int *i)
{
	tmp_token = ft_lstnew(msh, get_in(msh, line, *(&i)), IN);
	ft_lstadd_back(&msh->tokens, tmp_token);
}

void	handel_out0(t_minishell *msh, char *line, t_tokens *tmp_token, int *i)
{
	tmp_token = ft_lstnew(msh, get_out(msh, line, *(&i)), OUT);
	ft_lstadd_back(&msh->tokens, tmp_token);
}

void	handel_pipe0(t_minishell *msh, char *line, t_tokens *tmp_token, int *i)
{
	tmp_token = ft_lstnew(msh, get_pipe(msh, line, *(&i)), PIPE);
	ft_lstadd_back(&msh->tokens, tmp_token);
}

bool	handle_op(t_minishell *minishell, char *line, int *index)
{
	int			i;
	bool		b;
	t_tokens	*tmp_token;

	(1) && (tmp_token = NULL, b = false, i = *index);
	if (ft_ispipe(line[i]))
	{
		b = handle_pipe(minishell, line, i);
		if (b == false)
			handel_pipe0(minishell, line, tmp_token, &i);
	}
	else if (ft_isin(line[i]))
	{
		b = handle_in(minishell, line, &i);
		if (i == *index && b == false)
			handel_in0(minishell, line, tmp_token, &i);
	}
	else if (ft_isout(line[i]))
	{
		b = handle_out(minishell, line, &i);
		if (i == *index && b == false)
			handel_out0(minishell, line, tmp_token, &i);
	}
	return (*index = i, b);
}
