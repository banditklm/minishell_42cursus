/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:09:57 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/26 22:13:23 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

static void	helper_del(t_minishell *msh, t_tokens *tkn, t_tokens *tkn2, char *t)
{
	bool	b;

	b = false;
	while (tkn2 && (tkn2->type == BLANK))
		tkn2 = tkn2->next;
	if (tkn2->type == TEXT || tkn2->type == EXP || tkn2->type == CARD
		|| tkn2->type == S_QUOTE || tkn2->type == D_QUOTE)
	{
		while (tkn2 && (tkn2->type == TEXT || tkn2->type == EXP
				|| tkn2->type == S_QUOTE || tkn2->type == D_QUOTE
				|| tkn2->type == CARD))
		{
			if (tkn2->type == D_QUOTE || tkn2->type == S_QUOTE)
				b = true;
			(1) && (t = ft_strjoin(msh, t, tkn2->token), tkn2 = tkn2->next);
		}
		tkn = tkn->next;
		tkn->token = t;
		if (b == true)
			tkn->type = Q_DEL;
		else
			tkn->type = DEL;
		tkn->next = tkn2;
	}
}

void	get_del(t_minishell *msh)
{
	t_tokens	*token;
	t_tokens	*token2;
	char		*tmp;

	tmp = sdup(msh, &msh->local, "");
	token = msh->tokens;
	while (token)
	{
		if (token->next && token->type == HERDOC)
		{
			token2 = token->next;
			helper_del(msh, token, token2, tmp);
		}
		tmp = sdup(msh, &msh->local, "");
		token = token->next;
	}
}
