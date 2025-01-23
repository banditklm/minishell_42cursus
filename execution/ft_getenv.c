/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 05:24:49 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/26 10:27:02 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	*ft_getenv(char *var, t_minishell *msh)
{
	char	*tmp;
	size_t	len;
	int		check;
	int		i;

	i = 0;
	len = ft_strlen(var);
	while (msh->env[i])
	{
		tmp = sdup(msh, &msh->local, msh->env[i]);
		check = ft_strncmp(var, msh->env[i], ft_strlen(var));
		if (!check && msh->env[i][len] == '=')
		{
			tmp = tmp + len + 1;
			return (ft_strtrim(msh, tmp, " \t", true));
		}
		i++;
	}
	tmp = sdup(msh, &msh->local, "");
	return (tmp);
}
