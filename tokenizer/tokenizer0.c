/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:49:04 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/28 14:39:08 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

bool	handle_pipe(t_minishell *minishell, char *line, int index)
{
	int		i;
	bool	b;

	(1) && (i = index, b = false, i++);
	if (index == 0)
	{
		b = syntax_errorb(minishell, line, index);
		return (b);
	}
	if (ft_isblank(line[i]))
	{
		while (ft_isblank(line[i]) && line[i])
			i++;
		if (ft_ispipe(line[i]) || line[i] == '\0')
			b = syntax_errorb(minishell, line, i);
	}
	else if (ft_ispipe(line[i]))
		b = syntax_errorb(minishell, line, i);
	else if (line[i] == '\0')
		b = syntax_errorb(minishell, line, i);
	return (b);
}

bool	handle_in(t_minishell *minishell, char *ln, int *index)
{
	int			i;
	t_tokens	*tmp_token;
	bool		b;

	(1) && (i = *index, b = false, i++);
	if (ln[i] == '<')
	{
		b = handle_herdoc(minishell, ln, i);
		if (b == false)
		{
			(1) && (tmp_token = ft_lstnew(minishell,
				get_herdoc(minishell, ln, &i), HERDOC), *index = i);
			ft_lstadd_back(&minishell->tokens, tmp_token);
		}
	}
	else if (ln[i] == '|' || ln[i] == '>' || ln[i] == '\0')
		b = syntax_errorb(minishell, ln, i);
	else if (ft_isblank(ln[i]))
	{
		while (ft_isblank(ln[i]))
			i++;
		if (ln[i] == '|' || ln[i] == '<' || ln[i] == '>' || ln[i] == '\0')
			b = syntax_errorb(minishell, ln, i);
	}
	return (b);
}

bool	handle_out(t_minishell *msh, char *ln, int *index)
{
	int			i;
	t_tokens	*tmp_token;
	bool		b;

	(1) && (i = *index, b = false, i++);
	if (ln[i] == '>')
	{
		b = handle_append(msh, ln, i);
		if (b == false)
		{
			tmp_token = ft_lstnew(msh, get_append(msh, ln, &i), APPEND);
			ft_lstadd_back(&msh->tokens, tmp_token);
			*index = i;
		}
	}
	else if (ln[i] == '|' || ln[i] == '<' || ln[i] == '\0')
		b = syntax_errorb(msh, ln, i);
	else if (ft_isblank(ln[i]))
	{
		while (ft_isblank(ln[i]) && ln[i])
			i++;
		if (ln[i] == '|' || ln[i] == '<' || ln[i] == '>' || ln[i] == '\0')
			b = syntax_errorb(msh, ln, i);
	}
	return (b);
}

bool	handle_herdoc(t_minishell *minishell, char *line, int index)
{
	int		i;
	bool	b;

	(1) && (i = index, b = false, i++);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == '\0')
		b = syntax_errorb(minishell, line, i);
	else if (ft_isblank(line[i]))
	{
		while (ft_isblank(line[i]) && line[i])
			i++;
		if (line[i] == '|' || line[i] == '<'
			|| line[i] == '>' || line[i] == '\0')
			b = syntax_errorb(minishell, line, i);
	}
	return (b);
}

bool	handle_append(t_minishell *minishell, char *line, int index)
{
	int		i;
	bool	b;

	(1) && (i = index, b = false, i++);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == '\0')
		b = syntax_errorb(minishell, line, i);
	else if (ft_isblank(line[i]))
	{
		while (ft_isblank(line[i]))
			i++;
		if (line[i] == '|' || line[i] == '<'
			|| line[i] == '>' || line[i] == '\0')
			b = syntax_errorb(minishell, line, i);
	}
	return (b);
}
