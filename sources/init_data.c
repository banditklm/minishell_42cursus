/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:25:54 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:05:12 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_minishell *minishell, char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	minishell->global = NULL;
	minishell->local = NULL;
	minishell->env = ft_getfullenv(minishell, env);
	ft_free(&minishell->local, 0);
	rl_catch_signals = 0;
}

void	init_data2(t_minishell *minishell)
{
	minishell->sflag = 0;
	minishell->local = NULL;
	minishell->tokens = NULL;
	minishell->cmd = NULL;
	set_flag(0, true);
}

void	free_fd_local(t_minishell *msh, char *line)
{
	t_tokens	*t;

	t = msh->tokens;
	while (t)
	{
		if (t->fd != -1)
			close(t->fd);
		t = t->next;
	}
	ft_free(&msh->local, 0);
	msh->tokens = NULL;
	free(line);
	line = NULL;
}

int	all_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isblank(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

void	check_line1(t_minishell *minishell, char *line)
{
	if (!line)
	{
		if (minishell->env_checker)
			printf("\033[A\033[12C ");
		printf("exit\n");
		ft_exit_prog(minishell, 1);
	}
}
