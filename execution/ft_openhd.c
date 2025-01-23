/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openhd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:48:01 by sarif             #+#    #+#             */
/*   Updated: 2024/09/05 17:09:26 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	ft_creatfd_forhd(t_minishell *msh, char **input)
{
	int		fd;
	int		fdd;
	int		i;
	char	*file_path;

	i = -1;
	file_path = ft_getfile_name(msh);
	fd = open(file_path, O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Failed to open heredoc file\n", 2);
		ft_exit_prog(msh, 1);
	}
	fdd = open(file_path, O_RDONLY);
	if (fdd == -1)
	{
		ft_putstr_fd("Error: Failed to open heredoc file\n", 2);
		ft_exit_prog(msh, 1);
	}
	while (input && input[++i])
		(1) && (write(fd, input[i], ft_strlen(input[i])), write(fd, "\n", 1));
	close(fd);
	unlink(file_path);
	return (fdd);
}

int	handle_line(t_minishell *msh, t_tokens *token, char **store, int *flag)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, token->next->token))
		{
			free(line);
			if (set_flag(1, false))
				*flag = 1;
			break ;
		}
		if (token->next->type == DEL)
			line = herexp(msh, line);
		*store = ft_strjoin(msh, *store, line);
		*store = ft_strjoin(msh, *store, "\n");
		if (token->next->type == Q_DEL)
			free(line);
	}
	return (*store == NULL);
}

void	process_heredoc(t_minishell *msh, t_tokens *token, int *flag)
{
	char	*store;
	char	**input;

	store = NULL;
	handle_line(msh, token, &store, flag);
	if (*flag == 1)
		return ;
	input = ft_split(msh, store, '\n');
	token->fd = ft_creatfd_forhd(msh, input);
}

void	ft_openhd_norm(t_minishell *msh, t_tokens *token, int *flag)
{
	while (token)
	{
		if (token->type == HERDOC)
		{
			process_heredoc(msh, token, flag);
			if (*flag == 1)
				break ;
		}
		token = token->next;
	}
}

int	ft_openhd(t_minishell *msh)
{
	t_cmd		*cmd;
	t_tokens	*token;
	int			flag;

	cmd = msh->cmd;
	signal(SIGINT, sig_handler2);
	msh->stdin_org = dup(0);
	while (cmd)
	{
		flag = 0;
		token = cmd->tokens;
		ft_openhd_norm(msh, token, &flag);
		if (flag == 1)
			break ;
		cmd = cmd->next;
	}
	dup2(msh->stdin_org, STDIN_FILENO);
	close(msh->stdin_org);
	signal(SIGINT, sig_handler);
	return (flag);
}
