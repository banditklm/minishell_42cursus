/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:09:02 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/01 12:39:47 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	getlen_string(char *line, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (line[i] && ft_isstring(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	getlen_blank(char *line, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (line[i] && ft_isblank(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	getlen_op(char *line, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (line[i] && ft_isoperator(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	getlen_pipe(char *line, int index)
{
	int		i;
	int		count;

	i = index;
	count = 0;
	while (line[i] && ft_ispipe(line[i]))
	{
		count++;
		i++;
	}
	return (count);
}
