/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:07:15 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 14:22:03 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	isvalid_flag(char **av)
{
	int	j;
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1] == 'n')
		{
			j = 1;
			while (av[i][j])
			{
				if (av[i][j] != 'n')
					return (i);
				j++;
			}
		}
		else
			break ;
		i++;
	}
	return (i);
}

void	print_echo(t_minishell *msh, int fd, char **av, int i)
{
	while (av[(i)])
	{
		if (msh->pipes > 1)
		{
			printf("%s", av[i]);
			if (i != (ft_countline(av) - 1))
				printf(" ");
		}
		else
		{
			ft_putstr_fd(av[i], fd);
			if (i != (ft_countline(av) - 1))
				ft_putchar_fd(' ', fd);
		}
		(i)++;
	}
}

void	ft_echo(t_minishell *msh, t_cmd *cmd, bool fork)
{
	int	i;

	i = isvalid_flag(cmd->av);
	print_echo(msh, cmd->output, cmd->av, i);
	if (i <= 1 && msh->pipes > 1)
		printf("\n");
	else if (i <= 1 && msh->pipes == 1)
		ft_putchar_fd('\n', cmd->output);
	set_e_s_builtin(msh, fork, false);
}
