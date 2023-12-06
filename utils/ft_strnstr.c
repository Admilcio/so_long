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