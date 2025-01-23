/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:05:53 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/28 14:46:04 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

static int	is_del(char *line, int i, int n)
{
	i += 2;
	while (line[i] && i < n && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line [i] && line[i] != '<'
		&& line[i] != '>' && line[i] != '|' && i != n)
		return (1);
	else
		return (0);
}

void	open_heredocs(t_minishell *minishell, char *line, int n)
{
	int	i;
	int	s;
	int	d;
	int	flag;

	(1) && (s = 0, d = 0, i = 0, flag = 0);
	while (i < n)
	{
		if (line[i] == '"' && !s)
			d = !d;
		if (line[i] == '\'' && !d)
			s = !s;
		if (line[i] && line[i + 1] && line[i + 2] && s == 0 && d == 0
			&& is_del(line, i, n) && line[i] == '<' && line[i + 1] == '<')
		{
			i = ft_openhd_se(minishell, line, &i, &flag);
			if (flag == 1)
				break ;
		}
		i++;
	}
}

static int	dschecker(char *str, int *index, char c)
{
	(*index)++;
	while (str[*index])
	{
		if (str[*index] == c)
			return (1);
		(*index)++;
	}
	return (0);
}

static bool	sd_handler_help(t_minishell *msh, char *line, int *i)
{
	int		store;
	char	c;
	char	var[2];
	char	*error;

	if (line[*i] == '\"' || line[*i] == '\'')
	{
		(1) && (c = line[*i], store = *i);
		if (!dschecker(line, i, line[*i]))
		{
			open_heredocs(msh, line, store);
			if (msh->sflag)
				return (ft_exit_status(1, SET), true);
			else
			{
				(1) && (var[0] = c, var[1] = '\0', error = ft_strjoin(msh,
				"minishell: syntax error near unexpected token ", var),
				error = ft_strjoin(msh, error, "\n"));
				return (ft_putstr_fd(error, 2), ft_exit_status(258, SET), true);
			}
		}
	}
	return (false);
}

bool	sd_handler(t_minishell *msh, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (sd_handler_help(msh, line, &i))
			return (true);
	}
	return (false);
}
