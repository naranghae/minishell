#include "minishell_parsing.h"

int mini_trim(char *buf, int start, int end)
{	
	while (buf[start] == ' ' && start != end)
		start++;
	return (start);
}

size_t		ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}


char	*ft_strdup(const char *s1)
{
	char	*re;
	size_t	i;

	i = 0;
	re = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!re)
		return (0);
	while (s1[i] != '\0')
	{
		re[i] = s1[i];
		i++;
	}
	re[i] = '\0';
	return (re);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*re;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
		printf("len : %d\n", len);
	re = (char *)malloc(sizeof(char) * len + 1);
	if (!re)
		return (0);
	if (start >= ft_strlen(s))
		return (0);
	while (i < len)
		re[i++] = s[start++];
	re[i] = '\0';
	return (re);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*re;
	size_t		i;
	size_t		j;
	size_t		size;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(re = (char *)malloc(size + 1)))
		return (0);
	while (s1[i] != '\0')
	{
		re[i] = s1[i];
		i++;
	}
	re[i] = '\0';
	while (s2[j] != '\0')
	{
		re[i + j] = s2[j];
		j++;
	}
	re[i + j] = '\0';
	return (re);
}