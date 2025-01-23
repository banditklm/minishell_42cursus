/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:22:01 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/27 08:20:06 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isexpand(char c)
{
	if (c == '$' )
		return (1);
	else
		return (0);
}

int	ft_iswdcard(char c)
{
	if (c == '*' )
		return (1);
	else
		return (0);
}

int	ft_isblank(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}
