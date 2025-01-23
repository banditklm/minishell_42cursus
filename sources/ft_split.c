/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:50:28 by sarif             #+#    #+#             */
/*   Updated: 2024/08/24 19:02:27 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countword(char const *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			counter++;
		while (str[i] != c && str[i])
			i++;
	}
	return (counter);
}

static char	**ft_allocstr(t_minishell *msh, \
char **strings, char const *s, char c)
{
	int		count;
	int		j;
	int		i;

	count = ft_countword(s, c);
	j = 0;
	while (j < count)
	{
		while (*s == c)
			s++;
		i = 0;
		while (s[i] != c && s[i] != '\0')
			i++;
		strings[j] = ft_malloc(msh, &msh->local, (i + 1) * sizeof (char));
		ft_strlcpy(strings[j], (s), (i + 1));
		j++;
		s = s + i;
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(t_minishell *msh, char const *s, char c)
{
	char	**strings;
	int		count;

	if (!s)
		return (NULL);
	count = ft_countword(s, c);
	strings = ft_malloc(msh, &msh->local, (count + 1) * sizeof(char *));
	return (ft_allocstr(msh, strings, s, c));
}
