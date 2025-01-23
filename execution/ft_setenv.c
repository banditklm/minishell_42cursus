/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:50:23 by sarif             #+#    #+#             */
/*   Updated: 2024/08/27 10:26:18 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	**ft_setenv(t_minishell *msh)
{
	char	**env;
	char	*path;

	msh->env_checker = false;
	env = ft_malloc(msh, &msh->global, sizeof(char *) * 6);
	env[0] = strjoin_env(msh, "PATH=", "/usr/local/sbin:\
/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin");
	path = getcwd(NULL, 0);
	env[1] = strjoin_env(msh, "PWD=", path);
	free(path);
	path = NULL;
	env[2] = sdup(msh, &msh->global, "SHLVL=1");
	env[3] = sdup(msh, &msh->global, "_=/usr/bin/env");
	env[4] = sdup(msh, &msh->global, "OLDPWD");
	env[5] = NULL;
	return (env);
}
