/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:04:16 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 17:51:40 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	print_error_and_exit(t_minishell *msh, const char *str, bool fork)
{
	char	*error;

	if (fork)
		error = ft_strjoin(msh, "Minishell: exit: ", str);
	else
		error = ft_strjoin(msh, "exit\nMinishell: exit: ", str);
	error = ft_strjoin(msh, error, ": numeric argument required\n");
	ft_putstr_fd(error, 2);
	ft_exit_prog(msh, 255);
}

long	ft_atol(t_minishell *msh, const char *str, bool fork)
{
	long		result;
	int			sign;
	const char	*orig_str;

	(1) && (result = 0, sign = 1, orig_str = str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str) || ft_strlen(str) > 19)
		print_error_and_exit(msh, orig_str, fork);
	while (*str)
	{
		if (!ft_isdigit(*str))
			print_error_and_exit(msh, orig_str, fork);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

int	ft_exit_status(int status, t_type call)
{
	static int	e_status;

	if (call == SET)
		e_status = status;
	else if (call == GET)
		return (e_status);
	return (0);
}

void	ft_exit(t_minishell *msh, t_cmd *cmd, bool fork)
{
	long	nb;
	char	*str;

	if (cmd->av[1])
	{
		str = ft_strtrim(msh, cmd->av[1], " \t", false);
		nb = ft_atol(msh, str, fork);
		if (ft_countline(cmd->av) > 2)
		{
			ft_putstr_fd("exit\nMinishell: exit: too many arguments\n", 2);
			ft_exit_status(1, SET);
		}
		else
		{
			if (!fork)
				printf("exit\n");
			ft_exit_prog(msh, nb);
		}
	}
	else
	{
		if (!fork)
			printf("exit\n");
		ft_exit_prog(msh, ft_exit_status(0, GET));
	}
}
