/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:07:25 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:28 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;

	needlelen = ft_strlen(needle);
	if (!needle)
		return ((char *)haystack);
	while (*haystack && len > needlelen
		&& ft_strncmp(haystack, needle, needlelen))
	{
		haystack++;
		len--;
	}
	if (len >= needlelen && !ft_strncmp(haystack, needle, needlelen))
		return ((char *)haystack);
	return (NULL);
}
