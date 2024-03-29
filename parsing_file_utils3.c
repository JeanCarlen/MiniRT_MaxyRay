/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarlen <jcarlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:13:48 by fmalizia          #+#    #+#             */
/*   Updated: 2023/03/16 11:56:13 by jcarlen          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	*ft_realloc_rt_tab(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		new_ptr = malloc(size);
		return (new_ptr);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void	*ft_realloc_rt(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	old_size;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		new_ptr = malloc(size);
		return (new_ptr);
	}
	old_size = ft_strlen(ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	if (old_size < size)
		size = old_size;
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

int	contains_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
