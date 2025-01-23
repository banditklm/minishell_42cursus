/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:24:15 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 14:22:28 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	ft_pwd(t_minishell *msh, t_cmd *cmd, bool fork)
{
	char	*path;
	bool	free_it;

	free_it = true;
	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_to_dir(msh, cmd, true, fork);
		free_it = false;
	}
	if (msh->pipes > 1)
		printf("%s\n", path);
	else if (msh->pipes == 1)
		(1) && (ft_putstr_fd(path, cmd->output), \
		ft_putchar_fd('\n', cmd->output));
	if (free_it)
		free(path);
	set_e_s_builtin(msh, fork, false);
	path = NULL;
}
