/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 05:10:05 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 14:22:21 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	**set_variable(t_minishell *msh, char *var, bool plus)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_malloc(msh, &msh->global, \
sizeof (char *) * (ft_countline(msh->env) + 2));
	while (msh->env[++i])
		new_env[i] = msh->env[i];
	if (!plus)
		new_env[i] = sdup(msh, &msh->global, var);
	else
	{
		new_env[i] = strjoin_env(msh, get_var(msh, var, plus), "=");
		new_env[i] = strjoin_env(msh, new_env[i], get_v(msh, var));
	}
	i++;
	new_env[i] = NULL;
	ft_exit_status(0, SET);
	return (new_env);
}

int	find_eq(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*export_plus_eq(t_minishell *msh, char *env, char *value)
{
	bool	flag;
	char	*str;
	int		i;

	flag = false;
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			flag = true;
		i++;
	}
	if (flag)
		str = strjoin_env(msh, env, value);
	else
		(1) && (str = strjoin_env(msh, env, "="), \
		str = strjoin_env(msh, str, value));
	return (str);
}

void	export_var(t_minishell *msh, char *var, bool plus)
{
	int		i;
	char	*variable;

	i = -1;
	variable = get_var(msh, var, plus);
	if (!ft_strcmp(variable, "PATH"))
		msh->env_checker = true;
	while (msh->env[++i])
	{
		if (!ft_strcmp(variable, get_var(msh, msh->env[i], false)))
		{
			if (!find_eq(var, '='))
				return ;
			if (plus)
				msh->env[i] = export_plus_eq(msh, msh->env[i], \
				get_v(msh, var));
			else
				(1) && (msh->env[i] = strjoin_env(msh, variable, "="), \
				msh->env[i] = strjoin_env(msh, msh->env[i], get_v(msh, var)));
			ft_exit_status(0, SET);
			return ;
		}
	}
	msh->env = set_variable(msh, var, plus);
}

void	ft_export(t_minishell *msh, t_cmd *cmd, bool fork)
{
	int		i;
	char	*var;
	char	*error;

	i = 0;
	if (!cmd->av[1])
		print_export(msh, cmd);
	else
	{
		while (cmd->av[++i])
		{
			var = ft_getvariable(msh, cmd->av[i]);
			if (!check_invalid_id_export(var))
			{
				error = ft_strjoin(msh, "Minishell: export:\'", cmd->av[1]);
				error = ft_strjoin(msh, error, "\': not a valid identifier\n");
				ft_putstr_fd(error, 2);
				set_e_s_builtin(msh, fork, true);
				continue ;
			}
			else
				export_var(msh, cmd->av[i], ft_ispluseq(cmd->av[i]));
		}
	}
}
