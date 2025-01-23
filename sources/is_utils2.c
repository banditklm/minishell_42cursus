/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:22:03 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/12 23:57:17 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	ft_ispipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int	ft_isin(char c)
{
	if (c == '<')
		return (1);
	else
		return (0);
}

int	ft_isout(char c)
{
	if (c == '>')
		return (1);
	else
		return (0);
}
