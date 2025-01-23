/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:24:08 by sarif             #+#    #+#             */
/*   Updated: 2024/08/28 19:17:44 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources/minishell.h"

int	check_invalid_id_export(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (ft_isdigit(*str) || *str == '+')
		return (0);
	while (i < len - 1)
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	if (!(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '+'))
		return (0);
	return (1);
}

char	*get_v(t_minishell *msh, char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	value = ft_substr(msh, str, i + 1, ft_strlen(str));
	return (value);
}

bool	ft_ispluseq(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		return (true);
	else
		return (false);
}

char	*ft_getvariable(t_minishell *msh, char *str)
{
	size_t	i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = ft_substr(msh, str, 0, i);
	return (var);
}
