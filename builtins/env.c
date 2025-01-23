/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:57:18 by sarif             #+#    #+#             */
/*   Updated: 2024/08/24 09:44:52 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

bool	equalchr(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}

void	ft_env(t_minishell *msh, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (msh->env[i])
	{
		if (!msh->env_checker && !ft_strncmp("PATH=", msh->env[i], 5))
		{
			i++;
			continue ;
		}
		if (equalchr(msh->env[i]))
		{
			if (msh->pipes > 1)
				(1) && (printf("%s", msh->env[i]), printf("\n"));
			else
				(1) && (ft_putstr_fd(msh->env[i], cmd->output), \
				ft_putchar_fd('\n', cmd->output));
		}
		i++;
	}
}
