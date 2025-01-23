/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:35:42 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/01 14:39:07 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

bool	if_exp(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

int	lnx(char *token, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (token[i] && (token[i] != '$' && token[i] != ' '
			&& (ft_isalnum(*token) || *token == '_' || *token != '*')))
	{
		count++;
		i++;
	}
	return (count);
}

int	lnx1(char *token, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (token[i] && (token[i] != '$' && token[i] != ' '))
	{
		count++;
		i++;
	}
	return (count);
}

int	is_exit(char *herdoc)
{
	int		i;

	i = 0;
	while (herdoc[i])
	{
		if (herdoc[i] == '$' && herdoc[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

char	*handle_exit_s(t_minishell *msh, char *herdoc)
{
	char	*res;
	char	*rest;

	res = sdup(msh, &msh->local, ft_itoa(msh, ft_exit_status(0, GET)));
	rest = _sub(msh, herdoc, 1, ft_strlen(herdoc));
	res = ft_strjoin(msh, res, rest);
	return (res);
}
