/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:07:33 by sarif             #+#    #+#             */
/*   Updated: 2024/08/27 11:59:56 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

void	put_stderr(char *s)
{
	int	fd;

	fd = 2;
	while (*s)
		(write(fd, s, 1), s++);
}

char	*getlinepath(char *path, char *comm, t_cmd *cmd)
{
	char	**envpath;
	char	*com;
	int		i;

	i = -1;
	if (!comm)
		ft_exit_prog(cmd->msh, 0);
	if (ft_strchr(comm, '/') != NULL)
		return (sdup(cmd->msh, &cmd->msh->local, comm));
	envpath = ft_split(cmd->msh, path, ':');
	if (comm == NULL || ft_strlen(comm) == 0)
		getlinepath_norm(cmd->msh, comm);
	while (envpath[++i])
	{
		(1) && (com = NULL, com = ft_strjoin(cmd->msh, com, envpath[i]), com = \
		ft_strjoin(cmd->msh, com, "/"), com = ft_strjoin(cmd->msh, com, comm));
		if (access(com, F_OK) == 0)
			return (com);
	}
	getlinepath_norm(cmd->msh, comm);
	return (NULL);
}

int	isbuiltin(char *av)
{
	char	*builtin[8];
	int		i;

	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(av, builtin[i]))
			return (1);
		i++;
	}
	return (0);
}

int	getavlen(t_cmd *cmd)
{
	int			counter;
	t_tokens	*token;

	counter = 0;
	token = cmd->tokens;
	while (token)
	{
		if (token->next && token->type != TEXT)
			token = token->next;
		else
			counter++;
		token = token->next;
	}
	return (counter + 1);
}

void	args_maker(t_minishell *msh)
{
	t_tokens	*token;
	t_cmd		*cmd;
	int			i;

	cmd = msh->cmd;
	while (cmd)
	{
		cmd->av = ft_malloc(msh, &msh->local, sizeof(char *) * getavlen(cmd));
		token = cmd->tokens;
		i = 0;
		while (token)
		{
			if (!token->token[0] && token->ign)
				token = token->next;
			if (token && token-> next && token->type != TEXT)
				token = token->next;
			else if (token)
				cmd->av[i++] = sdup(msh, &msh->local, token->token);
			if (token)
				token = token->next;
		}
		cmd->av[i] = NULL;
		cmd = cmd->next;
	}
}
