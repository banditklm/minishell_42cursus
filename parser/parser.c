/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:55:39 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/07 22:59:19 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

bool	parser(t_minishell *minishell, char *line)
{
	bool	b;

	b = false;
	if (sd_handler(minishell, line) == true)
		return (true);
	else if (ft_tokenizer(minishell, line))
		return (true);
	else
		token_handler(minishell);
	return (b);
}
