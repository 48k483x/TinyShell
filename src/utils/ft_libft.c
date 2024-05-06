#include "../../minishell.h"

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
int _atoi(char *s)
{
    int i;
    int sign;
    int res;

    i = 0;
    res = 0;
    sign = 1;
    while (s[i] == ' ' && (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    return (res * sign);
}

int _strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
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


void *_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    return (ptr);
}

void *_memdel(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
    return NULL;
}