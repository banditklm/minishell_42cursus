/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:48:24 by sarif             #+#    #+#             */
/*   Updated: 2024/08/21 03:36:36 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	ft_redirection(t_cmd *cmd)
{
	if (cmd->input == 0 && cmd->c_idx != 0)
		cmd->input = cmd->fd[0];
	if (cmd->c_idx != cmd->msh->pipes - 1 && cmd->output == 1)
		cmd->output = cmd->fd[1];
	if (cmd->input != 0)
		dup2(cmd->input, STDIN_FILENO);
	if (cmd->output != 1)
		dup2(cmd->output, STDOUT_FILENO);
	if (cmd->next)
		close(cmd->fd[1]);
	if (cmd->next)
		close(cmd->fd[0]);
	if (cmd->input != 0)
		close(cmd->input);
	if (cmd->output != 1)
		close(cmd->output);
}
