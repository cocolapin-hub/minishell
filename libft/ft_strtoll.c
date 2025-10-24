
#include "../minishell.h"

static long long	edge(const char *nptr, int i, int sign, int *is_long)
{
	unsigned long long	abs_min;
	unsigned long long	result;
	int					digit;

	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (sign == 1 && result > ((unsigned long long)LLONG_MAX - digit) / 10)
		{
			*is_long = 0;
			return (LLONG_MAX);
		}
		if (sign == -1)
		{
			abs_min = (unsigned long long)LLONG_MAX + 1;
			if (result > (abs_min - digit) / 10)
				return (*is_long = 0, LLONG_MIN);
		}
		result = result * 10 + digit;
		i++;
	}
	return ((long long)result);
}

long long	ft_strtoll(const char *nptr, int *is_long)
{
	long long	result;
	int			sign;
	size_t		i;

	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = edge(nptr, i, sign, is_long);
	if (*is_long)
		result *= sign;
	return (result);
}
