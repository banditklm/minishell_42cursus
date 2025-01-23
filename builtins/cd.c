/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:29:34 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 17:45:03 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	*cd_no_arg_norm(t_minishell *msh, char *old_pwd, bool fork, char *pwd)
{
	char	*cur;

	cur = getcwd(NULL, 0);
	pwd = sdup(msh, &msh->global, cur);
	free(cur);
	cur = NULL;
	msh->env = set_oldpwd(msh, old_pwd);
	msh->env = set_pwd(msh, pwd);
	sort_env(msh->env, ft_countline(msh->env));
	set_e_s_builtin(msh, fork, false);
	return (pwd);
}

char	*get_to_dir(t_minishell *msh, t_cmd *cmd, bool get, bool fork)
{
	char		*old_pwd;
	static char	*pwd;
	char		*error;

	if (get)
		return (pwd);
	error = ft_strjoin(msh, "Minishell: cd: ", cmd->av[1]);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror(error);
		if (!ft_strcmp(cmd->av[1], "..") || !ft_strcmp(cmd->av[1], "."))
			(1) && (msh->env = set_oldpwd(msh, pwd), \
			pwd = strjoin_env(msh, strjoin_env(msh, pwd, "/"), \
			cmd->av[1]), msh->env = set_pwd(msh, pwd), chdir(cmd->av[1]));
		set_e_s_builtin(msh, fork, true);
	}
	else if (chdir(cmd->av[1]) == -1)
		perror(error);
	else
		pwd = cd_no_arg_norm(msh, old_pwd, fork, pwd);
	return (free(old_pwd), old_pwd = NULL, NULL);
}

char	**set_oldpwd(t_minishell *msh, char *old_pwd)
{
	int		i;
	int		check;
	char	**new_env;
	int		len;

	i = -1;
	check = 0;
	len = ft_countline(msh->env) + 2;
	new_env = ft_malloc(msh, &msh->global, sizeof (char *) * len);
	while (msh->env[++i])
	{
		if (!ft_strcmp("OLDPWD", get_key(msh, msh->env[i])))
		{
			new_env[i] = strjoin_env(msh, "OLDPWD=", old_pwd);
			check = 1;
		}
		else
			new_env[i] = msh->env[i];
	}
	if (!check)
		new_env[i++] = strjoin_env(msh, "OLDPWD=", old_pwd);
	new_env[i] = NULL;
	return (new_env);
}

void	cd_no_arg(t_minishell *msh, bool fork)
{
	char	*home;
	char	*old_pwd;
	char	*pwd;

	pwd = NULL;
	home = ft_getenv("HOME", msh);
	old_pwd = getcwd(NULL, 0);
	if (!home[0])
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		set_e_s_builtin(msh, fork, true);
	}
	else
	{
		if (chdir(home) == -1)
			perror(home);
		else
			pwd = cd_no_arg_norm(msh, old_pwd, fork, pwd);
	}
	free(old_pwd);
	old_pwd = NULL;
}

void	ft_cd(t_minishell *msh, t_cmd *cmd, bool fork)
{
	if (!cmd->av[1])
		cd_no_arg(msh, fork);
	else
		get_to_dir(msh, cmd, false, fork);
}
