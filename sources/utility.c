#include "../includes/so_long.h"

char	*long_strjoin(char *s1, char *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*result;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[len_s1 + i] = s2[i];
	result[len_s1 + i] = '\0';
	free(s1);
	free(s2);
	return (result);
}