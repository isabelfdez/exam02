#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int		i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_count(int n, int base_len)
{
	int		i = 1;
	while (n >= base_len)
	{
		i++;
		n /= base_len;
	}
	return (i);
}

void	ft_putnbr(int n, int base_len, char *base)
{
	if (n >= base_len)
		ft_putnbr(n / base_len, base_len, base);
	write(1, &base[n % base_len], 1);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int		ret = 0, width, pre, f_pre, neg, base_len, len, spa, zeros;
	long	num = 0;
	char	*str, *base, *s;

	va_start(ap, format);
	str = (char *)format;
	while (*str)
	{
		if (*str == '%')
		{
			width = 0, pre = 0, f_pre = 0, neg = 0, base_len = 0, len = 0, spa = 0, zeros = 0;
			str++;
			while ('0' <= *str && *str <= '9')
			{
				width = width * 10 + *str - '0';
				str++;
			}
			if (*str == '.')
			{
				str++;
				f_pre = 1;
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
				base_len = 10;
				base = "0123456789";
				num = va_arg(ap, int);
				if (num < 0)
				{
					neg = 1;
					num = num * (-1);
				}
				len = ft_count(num, base_len) + neg;
			}
			if (*str == 'x')
			{
				base_len = 16;
				base = "0123456789abcdef";
				num = va_arg(ap, unsigned);
				len = ft_count(num, base_len);
			}
			if (f_pre == 1 && pre > len && *str != 's')
				zeros = pre - len + neg;
			else if (f_pre == 1 && pre < len && *str == 's')
				len = pre;
			else if (f_pre == 1 && pre == 0 && (num == 0 || *str == 's'))
				len = 0;
			spa = width - len - zeros;
			while (spa-- > 0)
				ret += write(1, " ", 1);
			if (neg == 1)
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
	printf("|%20s| |%10.5d|\n", "hola mundo", 322);
	ft_printf("|%20s| |%10.5d|\n", "hola mundo", 322);

	return (0);
}
