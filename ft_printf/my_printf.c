/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:36:11 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/30 19:47:03 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void	ft_putnbr(int num, int base_len, char *base)
{
	if (num >= base_len)
		ft_putnbr(num / base_len, base_len, base);
	write(1, &base[num % base_len], 1);
}

int		ft_count(int n, int base_len)
{
	int i = 1;
	while (n >= base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int     ft_printf(const char *format, ...)
{
    va_list ap;
    int	ret = 0, len = 0, width = 0, pre = 0, f_pre = 0, zeros = 0, spa = 0, neg = 0, base_len = 0;
	long num = 0;
	char *str, *base, *s;
	va_start(ap, format);
	str = (char *)format;
	while (*str)
	{
		if (*str == '%')
		{
			len = 0, width = 0, pre = 0, f_pre = 0, zeros = 0, spa = 0, neg = 0, base_len = 0;
			str++;
			while ('0' <= *str && *str <= '9')
			{
				width = width * 10 + *str - '0';
				str++;
			}
			if (*str == '.')
			{
				f_pre = 1;
				str++;
				while ('0' <= *str && *str <= '9')
				{
					pre = pre * 10 + *str - '0';
					str++;
				}
			}
			if (*str == 's')
			{
				s = va_arg(ap, char *);
				if (!s)
					s = "(null)";
				len = ft_strlen(s);
			}
			if (*str == 'd')
			{
				num = va_arg(ap, int);
				if (num < 0)
				{
					neg = 1;
					num = num * (-1);
				}
				base = "0123456789";
				base_len = 10;
				len = ft_count(num, base_len) + neg;
			}
			if (*str == 'x')
			{
				num = va_arg(ap, unsigned);
				base = "0123456789abcdef";
				base_len = 16;
				len = ft_count(num, base_len);
			}
			if (f_pre == 1 && pre > len && *str != 's')
				zeros = pre - len + neg;
			else if (f_pre == 1 && pre < len && *str == 's')
				len = pre;
			else if (f_pre == 1 && pre == 0 && (num == 0 || *str == 's'))
				len = 0;
			spa = width - zeros - len;
			while (spa-- > 0)
				ret += write(1, " ", 1);
			if (neg)
				write(1, "-", 1);
			while (zeros-- > 0)
				ret += write(1, "0", 1);
			if (*str == 's')
				write(1, s, len);
			else if (len > 0)
				ft_putnbr(num, base_len, base);
			ret += len;
		}
		else
			ret += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (ret);
}

int main()
{
	int data = 6789102;
	printf("|%20s| |%10.5d|\n", "hola mundo", 322);
	ft_printf("|%20s| |%10.5d|\n", "hola mundo", 322);

	printf("|%20.3s| |%10.5x|\n", "hola mundo", data);
	ft_printf("|%20.3s| |%10.5x|\n", "hola mundo", data);

	return (0);
}
