#include "libft.h"

/*
**	@brief	return lenght null terminated string
**	
**	@param	str		pointer to string
**	@return	size_t	lenght string
*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
