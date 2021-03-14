/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:25:35 by nidescre          #+#    #+#             */
/*   Updated: 2019/11/05 17:18:29 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*first;

	(void)(*del);
	if (!lst)
		return (NULL);
	nlst = ft_lstnew((*f)(lst->content));
	first = nlst;
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&nlst, ft_lstnew((*f)(lst->content)));
		lst = lst->next;
	}
	return (first);
}
