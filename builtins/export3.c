/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:21:45 by sarif             #+#    #+#             */
/*   Updated: 2024/08/28 20:56:36 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	print_export_fork(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->msh->env[i])
	{
		j = 0;
		write (1, "declare -x ", 11);
		while (cmd->msh->env[i][j] && cmd->msh->env[i][j] != '=')
			write(1, &cmd->msh->env[i][j++], 1);
		if (cmd->msh->env[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while (cmd->msh->env[i][j])
				write(1, &cmd->msh->env[i][j++], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_export_value(char *env_var, int fd)
{
	int	j;

	j = 0;
	while (env_var[j] && env_var[j] != '=')
		ft_putchar_fd(env_var[j++], fd);
	if (env_var[j++] == '=')
	{
		ft_putstr_fd("=\"", fd);
		while (env_var[j])
			ft_putchar_fd(env_var[j++], fd);
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	print_export_env(t_minishell *msh, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (msh->env[++i])
	{
		if (!msh->env_checker && !ft_strncmp("PATH=", msh->env[i], 5))
			continue ;
		ft_putstr_fd("declare -x ", cmd->output);
		print_export_value(msh->env[i], cmd->output);
	}
}

void	print_export(t_minishell *msh, t_cmd *cmd)
{
	sort_env(msh->env, ft_countline(msh->env));
	if (msh->pipes > 1)
		print_export_fork(cmd);
	else
		print_export_env(msh, cmd);
}

char	*get_var(t_minishell *msh, char *str, bool plus)
{
	char	**store;

	store = ft_split(msh, str, '=');
	if (plus)
		store[0][ft_strlen(store[0]) - 1] = '\0';
	return (store[0]);
}
