/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 07:59:55 by kelmounj          #+#    #+#             */
/*   Updated: 2024/07/27 11:45:25 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	*get_in(t_minishell *minishell, char *line, int *index)
{
	int		i;
	int		j;
	char	*res;

	i = *index;
	j = 0;
	res = ft_malloc(minishell, &minishell->local, getlen_in(line, i) + 1);
	while (ft_isin(line[i]))
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = '\0';
	*index = i;
	return (res);
}

char	*get_out(t_minishell *minishell, char *line, int *index)
{
	int		i;
	int		j;
	char	*res;

	i = *index;
	j = 0;
	res = ft_malloc(minishell, &minishell->local, getlen_out(line, i) + 1);
	while (ft_isout(line[i]))
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = '\0';
	*index = i;
	return (res);
}

char	*get_herdoc(t_minishell *minishell, char *line, int *index)
{
	int		i;
	char	*res;

	i = *index;
	res = ft_malloc(minishell, &minishell->local, 3);
	ft_isin(line[i]);
	res[0] = '<';
	res[1] = '<';
	res[2] = '\0';
	i++;
	*index = i;
	return (res);
}

char	*get_append(t_minishell *minishell, char *line, int *index)
{
	int		i;
	char	*res;

	i = *index;
	res = ft_malloc(minishell, &minishell->local, 3);
	ft_isout(line[i]);
	res[0] = '>';
	res[1] = '>';
	res[2] = '\0';
	i++;
	*index = i;
	return (res);
}

char	*get_sq(t_minishell *minishell, char *line, int *index)
{
	int		i;
	int		j;
	char	*res;

	i = *index;
	j = 0;
	res = ft_malloc(minishell, &minishell->local, getlen_sq(line, i) + 1);
	i++;
	while (!ft_issnglqs(line[i]))
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
