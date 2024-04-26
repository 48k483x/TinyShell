#include "../minishell.h"

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

// void *_memcpy(void *dest, const void *src, size_t n)
// {
//     int i;

//     i = 0;
//     while (i < n)
//     {
//         ((char *)dest)[i] = ((char *)src)[i];
//         i++;
//     }
//     return (dest);
// }

// void *_realloc(void *ptr, size_t size)
// {
//     void *new;

//     if (!ptr)
//         return (malloc(size));
//     if (size == 0)
//     {
//         free(ptr);
//         return (NULL);
//     }
//     new = malloc(size);
//     if (!new)
//         return (NULL);
//     _memcpy(new, ptr, size);
//     free(ptr);
//     return (new);
// }

void *_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    return (ptr);
}