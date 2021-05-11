#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

int		main(void)
{
	char *str;
	char *name;
	char *contents;
	int i;
	str = (char *)malloc(sizeof(char) * 10);
	name = (char *)malloc(sizeof(char) * 5);
	contents = (char *)malloc(sizeof(char) * 4);
	for(int i = 0;i < 10;i++)
	{
		if (i == 5)
			str[i] = '=';
		else
			str[i] = 'a';
	}
	printf("%s\n", str);
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '=')
		{
			name = ft_substr(str, 0, i);
			contents = ft_substr(str, i + 1, strlen(str) - (i + 1));
		}
	}
	printf("name: %s\n", name);
	printf("contents: %s\n", contents);
	return (0);
}