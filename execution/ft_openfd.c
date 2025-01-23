/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:47:56 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 13:13:08 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	ft_append(t_minishell *msh, t_tokens *token)
{
	int		fd;
	char	*error;

	if (token->cmd->fd_fail)
		return (-1);
	if (token->boole || token->ign)
	{
		error = ft_strjoin(msh, "minishell: $", token->ambg);
		error = ft_strjoin(msh, error, ": ambigious redirect\n");
		ft_putstr_fd(error, 2);
		token->cmd->fd_fail = true;
		ft_exit_status(1, SET);
		return (-1);
	}
	fd = open(token->token, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		token->cmd->fd_fail = true;
		ft_putstr_fd("minishell🔻: ", 2);
		perror(token->token);
		ft_exit_status(1, SET);
	}
	token->fd = fd;
	return (fd);
}

int	ft_out(t_minishell *msh, t_tokens *token)
{
	int		fd;
	char	*error;

	if (token->cmd->fd_fail)
		return (-1);
	if (token->boole || token->ign)
	{
		error = ft_strjoin(msh, "minishell: $", token->ambg);
		error = ft_strjoin(msh, error, ": ambigious redirect\n");
		ft_putstr_fd(error, 2);
		token->cmd->fd_fail = true;
		ft_exit_status(1, SET);
		return (-1);
	}
	fd = open(token->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		token->cmd->fd_fail = true;
		ft_putstr_fd("minishell🔻: ", 2);
		perror(token->token);
		ft_exit_status(1, SET);
	}
	token->fd = fd;
	return (fd);
}

int	ft_in(t_minishell *msh, t_tokens *token)
{
	int		fd;
	char	*error;

	if (token->cmd->fd_fail)
		return (-1);
	if (token->boole || token->ign)
	{
		ft_putstr_fd("hna\n", 2);
		error = ft_strjoin(msh, "minishell: $", token->ambg);
		error = ft_strjoin(msh, error, ": ambigious redirect\n");
		ft_putstr_fd(error, 2);
		token->cmd->fd_fail = true;
		ft_exit_status(1, SET);
		return (-1);
	}
	fd = open(token->token, O_RDONLY, 0644);
	if (fd == -1)
	{
		token->cmd->fd_fail = true;
		ft_putstr_fd("minishell🔻: ", 2);
		perror(token->token);
		ft_exit_status(1, SET);
	}
	token->fd = fd;
	return (fd);
}

int	ft_openfd(t_cmd *cmd)
{
	t_tokens	*token;

	token = cmd->tokens;
	cmd->fd_fail = false;
	while (token)
	{
		if (cmd->fd_fail)
			break ;
		if (token->type == IN)
			cmd->input = ft_in(cmd->msh, token->next);
		else if (token->type == OUT)
			cmd->output = ft_out(cmd->msh, token->next);
		else if (token->type == APPEND)
			cmd->output = ft_append(cmd->msh, token->next);
		else if (token->type == HERDOC)
			cmd->input = token->fd;
		token = token->next;
	}
	if (cmd->fd_fail)
		return (0);
	return (1);
}
