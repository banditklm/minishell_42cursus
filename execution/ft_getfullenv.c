/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfullenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:50:02 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 14:00:21 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	ft_countline(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		i++;
	}
	return (i);
}

char	**ft_getfullenv(t_minishell *msh, char **env)
{
	char		**new_env;
	int			i;
	int			len;
	int			check;

	(1) && (i = -1, len = ft_countline(env) + 1, check = 0);
	if (!env || !*env)
		return (ft_setenv(msh));
	msh->env_checker = true;
	new_env = ft_malloc(msh, &msh->global, sizeof (char *) * (len + 3));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
			(1) && (env[i] = sdup(msh, &msh->global, "OLDPWD"), check = 1);
		new_env[i] = sdup(msh, &msh->global, env[i]);
	}
	if (!check)
		new_env[i++] = sdup(msh, &msh->global, "OLDPWD");
	new_env[i] = NULL;
	return (new_env);
}
