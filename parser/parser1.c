/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 08:40:57 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:17:09 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	get_len(char *token, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (token[i] && ((token[i] != '$')
			|| (token[i] == '$' && token[i + 1] == '$')
			|| (token[i] == '$' && !(token[i + 1]))))
	{
		count++;
		i++;
	}
	return (count);
}

int	is_expblank(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ' ')
		return (1);
	else
		return (0);
}

char	*helper_qexp2(t_minishell *msh, t_tokens *tkn, int *i)
{
	char		*s;
	char		*tmp;

	tmp = NULL;
	(1) && ((*i)++, s = _sub(msh, tkn->token, *i, lnx(tkn->token, *i)),
		*i = *i + lnx(tkn->token, *i));
	if (s[0] == '?')
		tmp = handle_exit(msh, s);
	else if (*s)
	{
		tmp = ft_getenv(get_key(msh, s), msh);
		tmp = ft_strjoin(msh, tmp, get_rest(msh, s));
	}
	else
		tmp = ft_strjoin(msh, "$", s);
	return (tmp);
}

void	helper_qexp(t_minishell *msh, t_tokens *tkn)
{
	char		*tmp;
	char		*tmp2;
	int			j[2];

	(1) && (tmp = NULL, tmp2 = NULL, j[0] = 0, j[1] = 0);
	while (tkn->token[j[0]])
	{
		if (!ft_isexpand(tkn->token[j[0]]) || (ft_isexpand(tkn->token[j[0]])
				&& ft_isexpand(tkn->token[j[0] + 1]))
			|| (ft_isexpand(tkn->token[j[0]]) && !(tkn->token[j[0] + 1])))
			(1) && (j[1] = get_len(tkn->token, j[0]),
					tmp = _sub(msh, tkn->token,
					j[0], j[1]), j[0] = j[0] + j[1]);
		else if (tkn->token[j[0]] == '$' && tkn->token[j[0] + 1] != '$')
			tmp = helper_qexp2(msh, tkn, &(j[0]));
		tmp2 = ft_strjoin(msh, tmp2, tmp);
	}
	tkn->token = tmp2;
}

void	qexp_handler(t_minishell *msh)
{
	t_tokens	*token_t;

	token_t = msh->tokens;
	while (token_t)
	{
		if (token_t->type == D_QUOTE)
		{
			if (if_exp(token_t->token) == true)
				helper_qexp(msh, token_t);
		}
		token_t = token_t->next;
	}
}
