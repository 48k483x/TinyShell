#include "../minishell.h"

size_t    _strlen(const char *s)
{
    size_t	i;

    i = 0;
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
