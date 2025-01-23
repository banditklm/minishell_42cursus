/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:06:16 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/28 12:26:52 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

static bool	is_ambiguous(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (true);
		i++;
	}
	return (false);
}

static void	handel_ambg(t_minishell *msh, t_tokens *tokens, char *val)
{
	t_tokens	*tmp_t;
	char		*var;
	char		**splited;
	int			i;

	tmp_t = tokens->next;
	var = sdup(msh, &msh->local, tokens->token);
	splited = ft_split0(msh, val, " \t");
	i = 0;
	tokens->ambg = sdup(msh, &msh->local, var);
	tokens->token = sdup(msh, &msh->local, splited[i++]);
	while (splited[i])
	{
		tokens->next = ft_lstnew(msh, splited[i], TEXT);
		tokens->next->boole = true;
		tokens->next->ambg = sdup(msh, &msh->local, var);
		tokens = tokens->next;
		i++;
	}
	tokens->next = tmp_t;
}

char	*handle_exit(t_minishell *msh, char *token)
{
	char	*res;
	char	*cut;

	cut = ft_substr(msh, token, 1, ft_strlen(token));
	res = ft_strjoin(msh, ft_itoa(msh, ft_exit_status(0, GET)), cut);
	return (res);
}

static void	exp_helper(t_minishell *msh, t_tokens *tkn, char *tmp)
{
	char		*key;

	key = get_key(msh, tkn->token);
	if (*key)
	{
		tmp = ft_getenv(key, msh);
		if (!tmp[0])
		{
			tkn->ign = true;
			tkn->ambg = sdup(msh, &msh->local, key);
		}
		tmp = ft_strjoin(msh, tmp, get_rest(msh, tkn->token));
		if (is_ambiguous(tmp) == true)
		{
			tkn->boole = true;
			handel_ambg(msh, tkn, tmp);
		}
		else
			tkn->token = sdup(msh, &msh->local, tmp);
	}
	else
		tkn->token = ft_strjoin(msh, "$", tkn->token);
}

void	expainding(t_minishell *msh)
{
	t_tokens	*tmp_token;
	t_tokens	*tmp_token2;
	char		*tmp;

	tmp_token = msh->tokens;
	while (tmp_token)
	{
		tmp_token2 = tmp_token;
		if (tmp_token2 && tmp_token2->next
			&& tmp_token2->type == EXP
			&& tmp_token2->next->type == TEXT)
		{
			tmp_token2 = tmp_token2->next;
			if (tmp_token2->token[0] == '?')
			{
				tmp = handle_exit(msh, tmp_token2->token);
				tmp_token2->token = sdup(msh, &msh->local, tmp);
			}
			else
				exp_helper(msh, tmp_token2, tmp);
			tmp_token->next = tmp_token2;
		}
		tmp_token = tmp_token->next;
	}
}
