/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:20:25 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/28 12:19:30 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_lstnew(t_minishell *msh, void *content, t_type type)
{
	t_tokens	*token;

	token = (t_tokens *)ft_malloc(msh, &msh->local, sizeof(t_tokens));
	token->fd = -1;
	token->token = content;
	token->type = type;
	token->boole = false;
	token->ign = false;
	token->next = NULL;
	return (token);
}

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

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

t_garbage	*ft_garnew(t_minishell *m, void *node)
{
	t_garbage	*garbage;

	garbage = (t_garbage *)malloc(sizeof(t_garbage));
	if (!garbage)
		return (free(node), ft_free(&m->local, 0)
			, ft_free(&m->global, 1), NULL);
	garbage->node = node;
	garbage->next = NULL;
	return (garbage);
}

void	ft_garadd_back(t_garbage **lst, t_garbage *new)
{
	t_garbage	*tmp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp && tmp -> next)
		tmp = tmp -> next;
	tmp -> next = new;
}

void	ft_garclear(t_garbage **lst)
{
	t_garbage	*tmp;
	t_garbage	*cur;

	tmp = *lst;
	while (tmp)
	{
		cur = tmp->next;
		free(tmp->node);
		free(tmp);
		tmp = cur;
	}
	*lst = NULL;
}
