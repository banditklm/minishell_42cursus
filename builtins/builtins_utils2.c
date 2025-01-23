/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:25:21 by sarif             #+#    #+#             */
/*   Updated: 2024/08/27 12:00:54 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	set_e_s_builtin(t_minishell *msh, bool fork, bool error)
{
	if (error)
	{
		if (fork)
			ft_exit_prog(msh, 1);
		else
			ft_exit_status(1, SET);
	}
	else
		if (!fork)
			ft_exit_status(0, SET);
}
