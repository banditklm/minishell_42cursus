/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:07:03 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 17:47:55 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	norm(t_minishell *msh, char *line)
{
	if (parser(msh, line) == true)
	{
		free_fd_local(msh, line);
		return (true);
	}
	if (ft_openhd(msh))
	{
		free_fd_local(msh, line);
		return (true);
	}
	return (false);
}

int	main(int ac, char **av, char **env)
{
	t_minishell			minishell;
	char				*line;
	struct termios		original_termios;

	init_data(&minishell, env, ac, av);
	tcgetattr(STDIN_FILENO, &original_termios);
	while (1 && isatty(STDIN_FILENO))
	{
		init_data2(&minishell);
		line = readline("Minishell🔻$ ");
		check_line1(&minishell, line);
		if (!line[0] || all_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (norm(&minishell, line))
			continue ;
		execution(&minishell);
		free_fd_local(&minishell, line);
		tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
	}
	return (ft_exit_status(0, GET));
}
