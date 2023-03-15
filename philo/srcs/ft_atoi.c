#include "philosophers.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f'
		|| c == '\n' || c == '\r'
		|| c == '\t' || c == '\v');
}

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	is_overflow(long current, long sign, char next)
{
	if (0 < sign)
	{
		if (INT_MAX / 10 < current)
			return (1);
		current = current * 10;
		if ((INT_MAX - current) < (next - '0'))
			return (1);
	}
	else
	{
		current = current * (-1);
		if (current < (INT_MIN / 10))
			return (1);
		current = current * 10;
		if (-(next - '0') < (INT_MIN - current))
			return (1);
	}
	return (0);
}

static long	do_conversion(char **s, long sign, bool *is_err)
{
	long	ret;
	char	*str;

	str = *s;
	ret = 0;
	while (ft_isdigit(*str))
	{
		if (is_overflow(ret, sign, *str))
		{
			*is_err = true;
			if (0 < sign)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		ret = ret * 10 + (*str - '0');
		str++;
	}
	*s = str;
	return (ret);
}

int	ft_atoi(const char *str)
{
	long	ret;
	long	sign;
	bool	is_err;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	is_err = false;
	ret = do_conversion((char **)&str, sign, &is_err);
	if (is_err || *str != '\0')
	{
		errno = ERANGE;
		if (*str != '\0')
			errno = EINVAL;
	}
	return ((int)(sign * ret));
}
