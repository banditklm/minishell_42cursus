/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 01:14:32 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/03 16:55:29 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

bool	ft_tokenizer0(t_minishell *msh, char *line, t_tokens *tmp_token, int *i)
{
	bool	b;

	b = false;
	if (ft_isblank(line[*i]))
	{
		tmp_token = ft_lstnew(msh, get_blank(msh, line, *(&i)), BLANK);
		ft_lstadd_back(&msh->tokens, tmp_token);
	}
	else if (ft_isoperator(line[*i]))
	{
		b = handle_op(msh, line, *(&i));
	}
	else if (ft_isexpand(line[*i]))
	{
		tmp_token = ft_lstnew(msh, get_exp(msh, *(&i)), EXP);
		ft_lstadd_back(&msh->tokens, tmp_token);
	}
	return (b);
}

void	ft_tokenizer1(t_minishell *msh, char *line, t_tokens *tmp_token, int *i)
{
	if (ft_isdblqs(line[*i]))
	{
		tmp_token = ft_lstnew(msh, get_dq(msh, line, *(&i)), D_QUOTE);
		ft_lstadd_back(&msh->tokens, tmp_token);
	}
	else if (ft_iswdcard(line[*i]))
	{
		tmp_token = ft_lstnew(msh, get_wdcard(msh, line, *(&i)), CARD);
		ft_lstadd_back(&msh->tokens, tmp_token);
	}
	else if (ft_isstring(line[*i]))
	{
		tmp_token = ft_lstnew(msh, get_string(msh, line, *(&i)), TEXT);
		ft_lstadd_back(&msh->tokens, tmp_token);
	}
	else
	{
		tmp_token = ft_lstnew(msh, get_sq(msh, line,*(&i)), S_QUOTE);
		ft_lstadd_back(&msh->tokens, tmp_token);
	}
}

bool	firstpipe(t_minishell *msh, char *line, int i)
{
	bool	b;

	b = false;
	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '|')
		{
			b = syntax_errorb(msh, line, i);
			return (b);
		}
		else
			return (b);
	}
	else
		return (b);
}

bool	ft_tokenizer(t_minishell *msh, char *line)
{
	int			i;
	bool		b;
	t_tokens	*tmp_token;

	(1) && (i = 0, b = false, tmp_token = NULL);
	if (firstpipe(msh, line, i))
		return (true);
	while (line[i])
	{
		if (ft_iswdcard(line[i]) || ft_issnglqs(line[i]) || ft_isdblqs(line[i])
			|| ft_isstring(line[i]))
		{
			ft_tokenizer1(msh, line, tmp_token, &i);
			continue ;
		}
		else
		{
			b = ft_tokenizer0(msh, line, tmp_token, &i);
			if (b)
				return (b);
			else if (b == false)
				continue ;
		}
	}
	return (b);
}
