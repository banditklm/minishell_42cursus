/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openhd1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:09:21 by sarif             #+#    #+#             */
/*   Updated: 2024/09/04 14:16:59 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	*ft_getfile_name(t_minishell *msh)
{
	char	*name;
	char	*path;

	name = ft_malloc(msh, &msh->local, 1);
	if (!name)
		return (perror("malloc"), NULL);
	path = ft_strjoin(msh, "/tmp/.tmp", ft_itoa(msh, (int)name));
	if (path)
		return (path);
	return (perror("malloc"), NULL);
}

static void	handle_input(char *del, int *flag)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, del))
		{
			free(line);
			if (set_flag(1, false))
				*flag = 1;
			break ;
		}
		free(line);
	}
}

static int	parse_del(t_minishell *minishell, char *line, int *j, int *flag)
{
	int		i;
	char	*del;

	i = *j + 2;
	del = NULL;
	while (ft_isblank(line[i]))
		i++;
	if (ft_isstring(line[i]))
		del = get_string(minishell, line, &i);
	else if (ft_isdblqs(line[i]) || ft_issnglqs(line[i++]))
		del = get_string(minishell, line, &(i));
	handle_input(del, flag);
	*j = i;
	return (0);
}

int	ft_openhd_se(t_minishell *minishell, char *line, int *i, int *flag)
{
	signal(SIGINT, sig_handler2);
	minishell->stdin_org = dup(0);
	parse_del(minishell, line, i, flag);
	dup2(minishell->stdin_org, STDIN_FILENO);
	close(minishell->stdin_org);
	return (signal(SIGINT, sig_handler), *i);
}
