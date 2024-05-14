#include "../../minishell.h"

int _isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

size_t	num_len(long nb)
{
	size_t	len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	if (nb == 0)
	{
		len++;
		return (len);
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void	*allocation_str(size_t len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (!(str))
		return (NULL);
	return (str);
}

char	*if_zero(char *str)
{
	str[0] = 48;
	return (str);
}

char	*_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == -2147483648)
		return (_strdup("-2147483648"));
	len = num_len((long)n);
	str = allocation_str(len);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		if_zero(str);
	while (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	while (n > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (str);
}