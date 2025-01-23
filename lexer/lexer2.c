/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 07:57:03 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/01 12:40:46 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	getlen_in(char *line, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (line[i] && ft_isin(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	getlen_out(char *line, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (line[i] && ft_isout(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	getlen_sq(char *line, int index)
{
	int	i;
	int	count;

	i = index;
	count = 0;
	i++;
	while (!ft_issnglqs(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	getlen_dq(char *line, int index)
{
	int	i;
	int	count;

	i = index;
	count = 0;
	i++;
	while (!ft_isdblqs(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

char	*get_dq(t_minishell *minishell, char *line, int *index)
{
	int		i;
	int		j;
	char	*res;

	i = *index;
	j = 0;
	res = ft_malloc(minishell, &minishell->local, getlen_dq(line, i) + 1);
	i++;
	while (!ft_isdblqs(line[i]))
	{
		res[j] = line[i];
		j++;
		i++;
	}
	i++;
	res[j] = '\0';
	*index = i;
	return (res);
}
