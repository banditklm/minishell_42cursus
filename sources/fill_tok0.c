/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tok0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:45:44 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:17:15 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stick_tok(t_minishell *m)
{
	t_tokens	*_t;
	t_tokens	*_t2;
	char		*tmp;

	(1) && (tmp = sdup(m, &m->local, ""), _t = m->tokens, _t2 = m->tokens);
	while (_t)
	{
		if ((_t->type == TEXT && _t->boole == false)
			|| _t->type == S_QUOTE
			|| _t->type == D_QUOTE || _t->type == EXP)
		{
			_t2 = _t;
			while (_t && ((_t->type == TEXT && _t->boole == false)
					|| _t->type == S_QUOTE || _t->type == D_QUOTE
					|| _t->type == EXP))
				(1) && (tmp = ft_strjoin(m, tmp, _t->token), _t = _t->next);
			(1) && (_t2->token = tmp, _t2->next = _t, tmp = NULL);
		}
		if (_t && _t->next)
			_t = _t->next;
		else
			break ;
	}
}

void	q_to_text(t_minishell *minishell)
{
	t_tokens	*tmp_token;

	tmp_token = minishell->tokens;
	while (tmp_token)
	{
		if (tmp_token->type == D_QUOTE || tmp_token->type == S_QUOTE)
			tmp_token->type = TEXT;
		tmp_token = tmp_token->next;
	}
}

void	exp_blank(t_minishell *minishell)
{
	t_tokens	*tmp_token;

	tmp_token = minishell->tokens;
	while (tmp_token)
	{
		if (tmp_token->next && tmp_token->type == EXP
			&& tmp_token->next->type == BLANK)
			tmp_token->type = TEXT;
		tmp_token = tmp_token->next;
	}
}

void	rm_exp(t_minishell *minishell)
{
	t_tokens	*tmp_token;

	if (minishell->tokens && minishell->tokens->next
		&& minishell->tokens->type == EXP
		&& (minishell->tokens->next->type == TEXT
			|| minishell->tokens->next->type == S_QUOTE
			|| minishell->tokens->next->type == D_QUOTE))
		minishell->tokens = minishell->tokens->next;
	tmp_token = minishell->tokens;
	while (tmp_token)
	{
		if (tmp_token->next && tmp_token->next->next
			&& tmp_token->next->type == EXP
			&& (tmp_token->next->next->type == D_QUOTE
				|| tmp_token->next->next->type == S_QUOTE
				|| tmp_token->next->next->type == TEXT))
			tmp_token->next = tmp_token->next->next;
		else
			tmp_token = tmp_token->next;
	}
}

void	rm_blank(t_minishell *minishell)
{
	t_tokens	*tmp_token;

	tmp_token = minishell->tokens;
	while (tmp_token && tmp_token->type == BLANK)
		tmp_token = tmp_token->next;
	minishell->tokens = tmp_token;
	while (tmp_token)
	{
		if (tmp_token->next && tmp_token->next->type == BLANK)
			tmp_token->next = tmp_token->next->next;
		else
			tmp_token = tmp_token->next;
	}
}
