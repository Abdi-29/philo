/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 13:03:40 by abba          #+#    #+#                 */
/*   Updated: 2022/03/13 12:41:57 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static char	*ft_whitespaces(char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\n' || \
			*s == '\v' || *s == '\f' || *s == '\r')
		s++;
	return (s);
}

static int	ft_sign(char *s, int *sign, int *neg)
{
	int	i;

	i = 0;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '+' || s[i] == '-')
		{
			*sign += 1;
			if (s[i] == '-')
				*neg *= -1;
		}
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		number;
	char	*str_copy;
	int		neg;

	str_copy = (char *)str;
	number = 0;
	sign = 0;
	neg = 1;
	str_copy = ft_whitespaces(str_copy);
	str_copy += ft_sign(str_copy, &sign, &neg);
	if (sign > 1)
	{
		return (0);
	}
	while (*str_copy)
	{
		if (!(ft_isdigit(*str_copy)))
			return (0);
		number = (*str_copy - 48) + (number * 10);
		str_copy++;
	}
	return (number * neg);
}
