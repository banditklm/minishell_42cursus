/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:44:01 by kelmounj          #+#    #+#             */
/*   Updated: 2024/09/05 01:01:40 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dstlen = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dstlen < dstsize && dst[dstlen])
		dstlen++;
	srclen = ft_strlen(src);
	if (!dst || !src)
		return (0);
	i = dstlen;
	while (j + dstlen + 1 < dstsize && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (dstlen + srclen);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	i = 0;
	while (src[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(t_minishell *msh, char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (sdup(msh, &msh->local, s2));
	if (!s2)
		return (sdup(msh, &msh->local, s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	str = ft_malloc(msh, &msh->local, len + 1);
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
