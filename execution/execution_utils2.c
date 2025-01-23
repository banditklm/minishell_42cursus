/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:20:04 by sarif             #+#    #+#             */
/*   Updated: 2024/08/28 12:13:25 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	handel_exit_sig(int exit_status)
{
	if (WTERMSIG(exit_status) == SIGINT)
		ft_exit_status(130, SET);
	else if (WTERMSIG(exit_status) == SIGQUIT)
		ft_exit_status(131, SET);
}

void	ft_waitpid_multicmd(t_minishell *msh, int *pid_store)
{
	int	i;
	int	exit_status;

	i = -1;
	while (++i < msh->pipes)
	{
		waitpid(pid_store[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			ft_exit_status(WEXITSTATUS(exit_status), SET);
		else if (WIFSIGNALED(exit_status))
			handel_exit_sig(exit_status);
	}
}

void	ft_waitpid_onecmd(t_minishell *msh, int pid)
{
	int		exit_status;

	if (waitpid(pid, &exit_status, 0) == -1)
		ft_exit_prog(msh, 1);
	if (WIFEXITED(exit_status))
		ft_exit_status(WEXITSTATUS(exit_status), SET);
	if (WTERMSIG(exit_status) == SIGINT)
		ft_exit_status(130, SET);
	else if (WTERMSIG(exit_status) == SIGQUIT)
		ft_exit_status(131, SET);
}

void	ft_child(t_minishell *msh, t_cmd *commande)
{
	if (!ft_openfd(commande))
		ft_exit_prog(msh, 1);
	ft_redirection(commande);
	is_a_dir_norm(msh, commande);
	if (isbuiltin(commande->av[0]))
	{
		handel_builtins(msh, commande, true);
		ft_exit_prog(msh, 0);
	}
	else
		execute_childe(commande);
}

void	getlinepath_norm(t_minishell *msh, char *comm)
{
	char	*error;

	error = ft_strjoin(msh, "Minishell: ", comm);
	error = ft_strjoin(msh, error, ": command not found\n");
	ft_putstr_fd(error, 2);
	ft_exit_prog(msh, 127);
}
