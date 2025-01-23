/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:04:12 by sarif             #+#    #+#             */
/*   Updated: 2024/08/26 18:04:56 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	is_a_dir_norm(t_minishell *msh, t_cmd *commande)
{
	struct stat	info;

	if (!stat(commande->av[0], &info) && S_ISDIR(info.st_mode))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(commande->av[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		ft_exit_prog(msh, 126);
	}
}
