/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:56:21 by sarif             #+#    #+#             */
/*   Updated: 2024/08/28 12:12:29 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

char	*strjoin_env(t_minishell *minishell, char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (sdup(minishell, &minishell->global, s2));
	if (!s2)
		return (sdup(minishell, &minishell->global, s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	str = ft_malloc(minishell, &minishell->global, len + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_substr(t_minishell *msh, char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (sdup(msh, &msh->global, ""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = ft_malloc(msh, &msh->global, len + 1);
	while (s[i] != '\0' && j < len)
	{
		ptr[j] = s[i + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str || fd < 0)
		return (0);
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (0);
}

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	write(fd, &c, 1);
	return (0);
}

char	**set_pwd(t_minishell *msh, char *pwd)
{
	int		i;
	int		check;
	char	**new_env;
	int		len;

	i = -1;
	check = 0;
	len = ft_countline(msh->env) + 2;
	new_env = ft_malloc(msh, &msh->global, sizeof (char *) * len);
	while (msh->env[++i])
	{
		if (!ft_strncmp("PWD", get_key(msh, msh->env[i]), 4))
		{
			new_env[i] = strjoin_env(msh, "PWD=", pwd);
			check = 1;
		}
		else
			new_env[i] = msh->env[i];
	}
	if (!check)
		new_env[i++] = strjoin_env(msh, "PWD=", pwd);
	new_env[i] = NULL;
	return (new_env);
}
