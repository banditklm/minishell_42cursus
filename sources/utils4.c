/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:47:16 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/04 14:22:46 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return (ptr + i);
		}
		i++;
	}
	if ((unsigned char)c == 0)
		return (ptr + i);
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
	{
		return (0);
	}
	while (i < n
		&& (*(unsigned char *)(s1 + i)) == (*(unsigned char *)(s2 + i)))
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((*(unsigned char *)(s1 + i)) - (*(unsigned char *)(s2 + i)));
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	if (ft_memcmp(dst, src, n) == 0)
		return (dst);
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

char	*add_spaces(t_minishell *msh, char *str, size_t i[2], size_t len)
{
	char	*new_str;

	new_str = str;
	if (i[0] > 0 && i[1] < len)
	{
		(1) && (new_str = ft_strjoin(msh, " ", str), \
		new_str = ft_strjoin(msh, new_str, " "));
	}
	else if (i[0] > 0)
		new_str = ft_strjoin(msh, " ", str);
	else if (i[1] < len)
		new_str = ft_strjoin(msh, str, " ");
	return (new_str);
}

char	*ft_strtrim(t_minishell *msh, char *s1, char *set, bool flag)
{
	int		i;
	int		len;
	char	*str;
	int		size;
	size_t	arg[2];

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len = ft_strlen(s1);
	if (i > len - 1)
		return (sdup(msh, &msh->local, ""));
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	size = len - i + 1;
	str = ft_malloc(msh, &msh->local, size * sizeof(char) + 1);
	str = ft_memcpy(str, (s1 + i), size);
	(1) && (str[size] = '\0', arg[0] = i, arg[1] = len + 1);
	if (flag)
		str = add_spaces(msh, str, arg, ft_strlen(s1));
	return (str);
}
