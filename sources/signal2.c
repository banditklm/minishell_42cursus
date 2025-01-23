/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:34:33 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/03 15:23:01 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler11(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	set_flag(int state, bool set)
{
	static int	flag;

	if (set)
		flag = state;
	return (flag);
}

void	sig_handler2(int sig)
{
	if (sig == SIGINT)
	{
		set_flag(1, true);
		ft_exit_status(1, SET);
		close(0);
	}
}
