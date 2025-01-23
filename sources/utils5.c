/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:22:24 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/01 15:20:32 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_newcmd(t_minishell *minishell, void *content)
{
	t_cmd		*cmd;

	cmd = (t_cmd *)ft_malloc(minishell, &minishell->local, sizeof(t_cmd));
	cmd->msh = minishell;
	cmd->tokens = content;
	cmd->input = 0;
	cmd->output = 1;
	cmd->fd_fail = false;
	cmd->next = NULL;
	return (cmd);
}

void	ft_addcmd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst && new)
	{
		if (*lst)
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			(tmp)->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_lstsize(t_cmd *lst)
{
	int	len;

	if (!lst)
		return (0);
	len = 1;
	while (lst -> next != NULL)
	{
		len++;
		lst = lst ->next;
	}
	return (len);
}

void	ft_exit_prog(t_minishell *msh, int status)
{
	t_tokens	*token;

	token = msh->tokens;
	while (token)
	{
		if (token->fd != -1)
			close(token->fd);
		token = token->next;
	}
	ft_free(&msh->local, 0);
	ft_free(&msh->global, 0);
	exit(status);
}

char	*_sub(t_minishell *msh, char const *s, unsigned int st, size_t len)
{
	char	*str;
	size_t	i;
	size_t	n;

	i = 0;
	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (n < st)
		return (sdup(msh, &msh->local, ""));
	if (len > n - st)
		len = n - st;
	str = ft_malloc(msh, &msh->local, (len + 1));
	while (i < len)
	{
		str[i] = s[st];
		i++;
		st++;
	}
	str[i] = '\0';
	return (str);
}
