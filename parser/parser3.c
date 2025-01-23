/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:06:45 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:22:34 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

static int	get_len(char *token, int index)
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

char	*herexp_helper(t_minishell *msh, char *herdoc, int *i)
{
	char	*tmp;
	char	*str;

	(1) && ((*i)++, str = _sub(msh, herdoc, *i, lnx1(herdoc, *i)),
	*i = *i + lnx1(herdoc, *i));
	if (*str == '?')
		tmp = handle_exit_s(msh, str);
	else if (*str)
		(1) && (tmp = ft_getenv(get_key(msh, str), msh)
			, tmp = ft_strjoin(msh, tmp, get_rest(msh, str)));
	else
		tmp = ft_strjoin(msh, "$", str);
	return (tmp);
}

char	*herexp(t_minishell *msh, char *herdoc)
{
	char		*tmp;
	char		*tmp2;
	int			i;
	int			len;

	tmp = sdup(msh, &msh->local, "");
	tmp2 = sdup(msh, &msh->local, "");
	(1) && (i = 0, len = 0);
	while (herdoc[i])
	{
		if (!ft_isexpand(herdoc[i]) || (ft_isexpand(herdoc[i])
				&& ft_isexpand(herdoc[i + 1]))
			|| (ft_isexpand(herdoc[i])
				&& !(herdoc[i + 1])))
			(1) && (len = get_len(herdoc, i),
					tmp = _sub(msh, herdoc, i, len), i = i + len);
		else if (herdoc[i] == '$' && herdoc[i + 1] != '$')
			tmp = herexp_helper(msh, herdoc, &i);
		tmp2 = ft_strjoin(msh, tmp2, tmp);
	}
	return (free(herdoc), herdoc = NULL, tmp2);
}

char	*get_key(t_minishell *msh, char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (ft_isdigit(*str) || *str == '*')
		i++;
	else
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				break ;
			i++;
		}
	}
	key = _sub(msh, str, 0, i);
	return (key);
}

char	*get_rest(t_minishell *msh, char *str)
{
	size_t	i;
	char	*rest;

	i = 0;
	if (ft_isdigit(*str) || *str == '*')
		i++;
	else
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				break ;
			i++;
		}
	}
	if (i == ft_strlen(str))
		return (NULL);
	rest = _sub(msh, str, i, ft_strlen(str));
	return (rest);
}
