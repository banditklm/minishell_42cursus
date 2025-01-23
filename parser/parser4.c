/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:24:56 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:11:20 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	size_token(t_minishell *msh)
{
	t_tokens	*tkn;
	int			size;

	tkn = msh->tokens;
	size = 0;
	while (tkn)
	{
		size++;
		tkn = tkn->next;
	}
	return (size);
}

static DIR	*error_dir(void)
{
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		exit(0);
	}
	return (dir);
}

void	filldir(t_tokens *tkn, t_minishell *msh)
{
	t_tokens		*taker;
	t_tokens		*t;
	struct dirent	*d;
	DIR				*dir;

	(1) && (dir = error_dir(), t = tkn, taker = tkn->next, d = readdir(dir));
	while (d->d_name[0] == '.')
		d = readdir(dir);
	if (!d)
		return ;
	if (d->d_name[0] != '.')
		(1) && (t->token = sdup(msh, &msh->local, d->d_name), t->type = TEXT,
		t->next = ft_lstnew(msh, sdup(msh, &msh->local, " "), BLANK),
		t = t->next);
	d = readdir(dir);
	while (d != NULL)
	{
		if (d->d_name[0] != '.')
			(1) && (t->next = ft_lstnew(msh, sdup(msh, &msh->local, d->d_name),
				TEXT), t = t->next, t->next = ft_lstnew(msh,
				sdup(msh, &msh->local, " "), BLANK), t = t->next);
		d = readdir(dir);
	}
	t->next = taker;
	closedir(dir);
}

int	check_card(t_tokens *tkn)
{
	t_tokens	*token;

	token = tkn;
	if ((ft_isoperator(token->token[0]) || token->type == BLANK
			|| (token->type == D_QUOTE && !ft_strlen(token->token))
			|| (token->type == S_QUOTE && !ft_strlen(token->token)))
		&& (token->next && token->next->type == CARD) && (((token->next->next
					&& token->next->next->type != TEXT
					&& token->next->next->type != D_QUOTE
					&& token->next->next->type != S_QUOTE
					&& token->next->next->type != EXP))
			|| !token->next->next))
		return (1);
	else
		return (0);
}

void	wildcard(t_minishell *msh)
{
	t_tokens		*token;

	token = msh->tokens;
	if (token->type == CARD && (token->next
			&& !ft_isoperator(token->next->token[0])
			&& token->next->type != BLANK))
		token->type = TEXT;
	else if (token->type == CARD)
		filldir(token, msh);
	while (token)
	{
		if (check_card(token))
			filldir(token->next, msh);
		token = token->next;
	}
}
