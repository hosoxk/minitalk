/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:27:25 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/04/24 23:30:16 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s);
	dest = (char *)malloc(size * sizeof(char) + 1);
	if (dest == NULL)
		return (0);
	ft_memcpy(dest, s, size);
	dest[size] = '\0';
	return (dest);
}
