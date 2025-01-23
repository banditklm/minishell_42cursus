/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:26:49 by sarif             #+#    #+#             */
/*   Updated: 2024/08/27 12:00:29 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	signal_norm(t_minishell *msh, int flag)
{
	if (flag == 1)
	{
		if (ft_strcmp(msh->cmd->av[0], "./minishell") == 0)
		{
			signal(SIGINT, sig_handler0);
			signal(SIGQUIT, SIG_IGN);
		}
		else
		{
			signal(SIGINT, sig_handler11);
			signal(SIGQUIT, sig_handler11);
		}
	}
	else
	{
		if (ft_strcmp(msh->cmd->av[0], "./minishell") == 0)
			(1) && (signal(SIGQUIT, SIG_IGN), signal(SIGINT, sig_handler0));
		else
			(1) && (signal(SIGQUIT, sig_handler1),
			signal(SIGINT, sig_handler1));
	}
}

char	*ft_error(t_cmd *cmd, char *av)
{
	char	*line;

	line = NULL;
	if (av[0] == '.' && av[1] == '/')
		line = ft_substr(cmd->msh, av, 2, ft_strlen(av));
	else
		line = sdup(cmd->msh, &cmd->msh->local, av);
	line = ft_strjoin(cmd->msh, "Minishell: ", line);
	return (line);
}

char	*handel_cmd(t_cmd *cmd)
{
	char	*new_line;

	new_line = NULL;
	new_line = ft_strjoin(cmd->msh, "./", cmd->av[0]);
	cmd->av[0] = ft_strjoin(cmd->msh, "./", cmd->av[0]);
	return (new_line);
}

int	ft_fork_process(t_minishell *msh, t_cmd *commande, int *pid_store, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Minishell: fork: ");
		return (-1);
	}
	if (pid == 0)
		ft_child(msh, commande);
	pid_store[i] = pid;
	return (pid);
}

void	ft_setup_pipes(t_cmd *commande, t_cmd *tmp)
{
	close(commande->fd[1]);
	if (tmp)
		close(tmp->fd[0]);
	if (commande->next)
		commande->next->input = commande->fd[0];
}
