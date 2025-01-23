/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:08:44 by sarif             #+#    #+#             */
/*   Updated: 2024/08/26 18:04:47 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	execute_onecmd(t_cmd *cmd)
{
	char	*path;
	char	*line;
	pid_t	pid;

	signal_norm(cmd->msh, 0);
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd->output, STDOUT_FILENO);
		dup2(cmd->input, STDIN_FILENO);
		is_a_dir_norm(cmd->msh, cmd);
		path = ft_getenv("PATH", cmd->msh);
		if (!path[0])
			line = handel_cmd(cmd);
		else
			line = getlinepath(path, cmd->av[0], cmd);
		if (execve(line, cmd->av, cmd->msh->env) == -1)
		{
			perror(ft_error(cmd, cmd->av[0]));
			ft_exit_prog(cmd->msh, 1);
		}
	}
	ft_waitpid_onecmd(cmd->msh, pid);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	ft_onepipe(t_cmd *cmd)
{
	if (!ft_openfd(cmd))
		return ;
	if (isbuiltin(cmd->av[0]))
		handel_builtins(cmd->msh, cmd, false);
	else
		execute_onecmd(cmd);
}

void	execute_childe(t_cmd *cmd)
{
	char	*path;
	char	*line;

	path = ft_getenv("PATH", cmd->msh);
	line = getlinepath(path, cmd->av[0], cmd);
	if (execve(line, cmd->av, cmd->msh->env) == -1)
	{
		perror("Error: ");
		ft_exit_prog(cmd->msh, 1);
	}
}

void	ft_multi_pipes(t_minishell *msh)
{
	int		i;
	int		*pid_store;
	t_cmd	*commande;
	t_cmd	*tmp;

	tmp = NULL;
	i = -1;
	commande = msh->cmd;
	signal_norm(msh, 1);
	pid_store = ft_malloc(msh, &msh->local, sizeof(int) * msh->pipes);
	while (++i < msh->pipes)
	{
		pipe(commande->fd);
		if (ft_fork_process(msh, commande, pid_store, i) == -1)
			return ;
		ft_setup_pipes(commande, tmp);
		tmp = commande;
		commande = commande->next;
	}
	close(tmp->fd[0]);
	ft_waitpid_multicmd(msh, pid_store);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	execution(t_minishell *ms)
{
	t_cmd	*commande;

	commande = ms->cmd;
	args_maker(ms);
	ms->pipes = ft_lstsize(commande);
	if (ms->pipes == 1)
		ft_onepipe(commande);
	else if (ms->pipes > 1)
		ft_multi_pipes(ms);
}
