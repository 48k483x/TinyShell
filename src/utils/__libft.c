#include "../../minishell.h"

int _strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    if (!src || !dest)
        return (0);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (i);
}

char *_strjoin(char *dest, char *src)
{
    int i;
    int j;
    char *cat;
    int len;

    if (!dest || !src)
        return (NULL);
    len = _strlen(dest) + _strlen(src);
    cat = malloc(sizeof(char *) * (len + 1));
    if (!cat)
        return (NULL);
    i = 0;
    j = 0;
    while (dest[j])
        cat[i++] = dest[j++];
    j = 0;
    while (src[j])
        cat[i++] = src[j++];
    cat[i] = '\0';
    return (cat);

}

size_t    _strlen(const char *s)
{
    size_t	i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

char *_strcat(char *dest, char *src)
{
	int i;
    int j;
    char *cat;
    int len;

    if (!dest || !src)
        return (NULL);
    len = _strlen(dest) + _strlen(src);
    cat = malloc(sizeof(char *) * (len + 1));
    if (!cat)
        return (NULL);
    i = 0;
    j = 0;
    while (dest[j])
        cat[i++] = dest[j++];
    j = 0;
    while (src[j])
        cat[i++] = src[j++];
    cat[i] = '\0';
    return (cat);
}

char	*_strdup(const char *s1)
{
	int		i;
	char	*a;

	if (s1 == NULL)
		return (NULL);
	a = malloc(_strlen(s1) + 1);
	if (a == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}




