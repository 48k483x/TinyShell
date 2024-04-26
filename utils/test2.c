#include "../minishell.h"
char *ft_strtrim_inplace(char *s) 
{
  if (s == NULL) 
    return NULL;
  while (*s == ' ' && *s != '\0')
    s++;
  if (*s == '\0')
    return s;
  char *end = s + _strlen(s) - 1;
  while (*end == ' ' && end > s) {
    end--;
  }

  *(end + 1) = '\0';

  return s;
}
