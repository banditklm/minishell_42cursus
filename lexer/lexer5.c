/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:23:08 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/27 08:24:17 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	get_lencard(char *line, int index)
{
	int	i;
	int	count;

	i = index;
	count = 0;
	while (line[i] && line[i] == '*')
	{
		count++;
		i++;
	}
	return (count);
}

char	*get_wdcard(t_minishell *minishell, char *line, int *index)
{
	int		i;
	int		j;
	char	*res;

	i = get_lencard(line, *index);
	j = 0;
	res = ft_malloc(minishell, &minishell->local, i + 1);
	while (i > 0)
	{
		res[j] = line[*index];
		j++;
		(*index)++;
		i--;
	}
	res[j] = '\0';
	return (res);
}
