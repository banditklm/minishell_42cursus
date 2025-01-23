/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 00:59:20 by sarif             #+#    #+#             */
/*   Updated: 2024/09/03 13:39:35 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	check_invalid_id(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

void	sort_env(char **env, int size)
{
	int		i;
	char	*temp;
	int		j;

	i = -1;
	while (++i < size - 1)
	{
		j = 0;
		while (j < size)
		{
			if (env[j] == NULL)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			else if (env[j + 1] != NULL && ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
	}
}

static void	ft_print_error_norm(t_minishell *msh, bool fork, t_cmd *cmd)
{
	char	*error;

	error = ft_strjoin(msh, "Minishell: unset:\'", cmd->av[1]);
	error = ft_strjoin(msh, error, "\': not a valid identifier\n");
	ft_putstr_fd(error, 2);
	set_e_s_builtin(msh, fork, true);
}

void	ft_unset(t_minishell *msh, t_cmd *cmd, bool fork)
{
	int		i;
	int		count_line;
	int		j;

	i = -1;
	if (cmd->av[1] && !check_invalid_id(cmd->av[1]))
	{
		ft_print_error_norm(msh, fork, cmd);
		return ;
	}
	while (cmd->av[++i])
	{
		j = 0;
		count_line = ft_countline(msh->env);
		while (msh->env[j])
		{
			if (!ft_strcmp(cmd->av[i], get_var(msh, msh->env[j], false)))
			{
				msh->env[j] = NULL;
				sort_env(msh->env, count_line - 1);
			}
			j++;
		}
	}
}
