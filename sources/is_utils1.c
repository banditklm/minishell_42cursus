/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:38:54 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/09 16:18:56 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isstring(char c)
{
	if (!ft_isblank(c) && c != '|' && c != '$' && c != '"' && c != '\''
		&& c != '<' && c != '>')
		return (1);
	else
		return (0);
}

int	ft_issnglqs(char c)
{
	if (c == '\'')
		return (1);
	else
		return (0);
}

int	ft_isdblqs(char c)
{
	if (c == '"')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}
