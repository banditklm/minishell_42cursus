/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tok1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:40:37 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/01 15:16:20 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd(t_minishell *minishell)
{
	t_tokens	*token1;
	t_tokens	*token2;
	t_tokens	*token3;
	t_cmd		*cmd;
	int			index;

	(1) && (cmd = NULL, index = 0, token1 = minishell->tokens,
		token2 = minishell->tokens);
	while (token1)
	{
		while (token1 && token1->next && token1->next->type != PIPE)
			token1 = token1->next;
		token3 = token1;
		if (token1 && token1->next && token1->next->type == PIPE)
			token1 = token1->next->next;
		else if (token1)
			token1 = token1->next;
		token3->next = NULL;
		cmd = ft_newcmd(minishell, token2);
		cmd->c_idx = index++;
		ft_addcmd_back(&minishell->cmd, cmd);
		token2 = token1;
	}
}

void	token_cmd(t_minishell *minishell)
{
	t_cmd		*cmd;
	t_tokens	*tokens;

	cmd = minishell->cmd;
	while (cmd)
	{
		tokens = cmd->tokens;
		while (tokens)
		{
			tokens->cmd = cmd;
			tokens = tokens->next;
		}
		cmd = cmd->next;
	}
}

void	token_index(t_minishell *minishell)
{
	t_cmd		*cmd;
	t_tokens	*tokens;
	int			index;

	index = 0;
	cmd = minishell->cmd;
	while (cmd)
	{
		tokens = cmd->tokens;
		while (tokens)
		{
			tokens->t_idx = index;
			index++;
			tokens = tokens->next;
		}
		index = 0;
		cmd = cmd->next;
	}
}

void	card_to_text(t_minishell *msh)
{
	t_tokens	*token;

	token = msh->tokens;
	while (token)
	{
		if (token->type == CARD)
			token->type = TEXT;
		token = token->next;
	}
}
