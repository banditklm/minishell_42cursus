/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:38:27 by kelmounj          #+#    #+#             */
/*   Updated: 2024/08/28 20:38:37 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_garbage **garbage, int boole)
{
	ft_garclear(garbage);
	if (boole)
	{
		write(2, "Allocation error\n", 17);
		exit(1);
	}
}

void	*ft_malloc(t_minishell *msh, t_garbage **garbage, size_t size)
{
	t_garbage	*tmp_garbage;
	void		*new;

	tmp_garbage = NULL;
	new = malloc(size);
	if (!new)
		return (ft_free(&msh->local, 0), ft_free(&msh->global, 1), NULL);
	tmp_garbage = ft_garnew(msh, new);
	ft_garadd_back(garbage, tmp_garbage);
	return (new);
}
