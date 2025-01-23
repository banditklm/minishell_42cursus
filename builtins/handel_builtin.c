/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:04:10 by sarif             #+#    #+#             */
/*   Updated: 2024/08/24 09:46:41 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	handel_builtins(t_minishell *msh, t_cmd *cmd, bool fork)
{
	if (!ft_strcmp(cmd->av[0], "env"))
		ft_env(msh, cmd);
	if (!ft_strcmp(cmd->av[0], "exit"))
		ft_exit(msh, cmd, fork);
	if (!ft_strcmp(cmd->av[0], "pwd"))
		ft_pwd(msh, cmd, fork);
	if (!ft_strcmp(cmd->av[0], "unset"))
		ft_unset(msh, cmd, fork);
	if (!ft_strcmp(cmd->av[0], "echo"))
		ft_echo(msh, cmd, fork);
	if (!ft_strcmp(cmd->av[0], "cd"))
		ft_cd(msh, cmd, fork);
	if (!ft_strcmp(cmd->av[0], "export"))
		ft_export(msh, cmd, fork);
}
