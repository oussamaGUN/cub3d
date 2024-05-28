#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
int ft_putstr(char *str)
{
	if (!str)
		return ft_putstr("(null)");
	int i = -1;
	int len = 0;
	while (str[++i])
		len += write(1, &str[i], 1);
	return len;
}
int ft_putchar(char c)
{
	return write(1, &c, 1);
}
int ft_putnbr(long long int n)
{
	int len = 0;
	long long int n1 = n;
	if (n1 <= 0)
		len++, n1 *= -1;
	while (n1)
	{
		n1 /= 10;
		len++;
	}
	if (n == INT_MIN)
		ft_putstr("-2147483648");
	else if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		ft_putnbr(n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n < 10)
		ft_putchar(n + '0');
	return len;
}
int ft_puthex(long long int n)
{
	int len = 0;
	char base[16] = "0123456789abcdef";
	char res[100];
	int i = 0;
	while (n)
	{
		res[i++] = base[n % 16];
		n /= 16;	
	}
	res[i] = '\0';
	i--;
	while (i >=0)
		len += ft_putchar(res[i--]);
	return len;
}
int ft_printf(const char *s, ... )
{
	va_list str;
	va_start(str, s);
	int i = -1;
	int len = 0;
	while (s[++i])
	{		
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 's')
				len += ft_putstr(va_arg(str, char *));
			else if (s[i] == 'd')
				len += ft_putnbr((long long int)va_arg(str, int));
			else if (s[i] == 'x')
				len += ft_puthex((long long int)va_arg(str, unsigned int));
		}
		else
			len += ft_putchar(s[i]);
		
	}
	va_end(str);
	return len;
}
int main(void)
{
    int len;
    int len2;
    unsigned int ui;
    void *addr;

    len = ft_printf("Let's try to printf a simple sentence.\n");
    len2 = printf("Let's try to printf a simple sentence.\n");
    ui = (unsigned int)INT_MAX + 1024;
    addr = (void *)0x7ffe637541f0;
    ft_printf("Length:[%d, %d]\n", len, len);
    printf("Length:[%d, %d]\n", len2, len2);
    ft_printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);
    ft_printf("Unsigned:[%d]\n", ui);
    printf("Unsigned:[%d]\n", ui);
    ft_printf("Unsigned hexadecimal:[%x, %x]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %x]\n", ui, ui);
    ft_printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");
    len = ft_printf("Percent:[h]\n");
    len2 = printf("Percent:[h]\n");
    ft_printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);
    return (0);
}
