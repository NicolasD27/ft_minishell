/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:27:08 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/05 17:11:13 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst;

	if (alst)
	{
		if ((*alst))
		{
			lst = *alst;
			while (lst->next)
				lst = lst->next;
			lst->next = new;
		}
		else
			*alst = new;
	}
}
