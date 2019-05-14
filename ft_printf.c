/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:33:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 15:02:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				everything_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	if ((*flags << 40) >> 56 == 'c' || (*flags << 40) >> 56 == 'C' || (*flags << 40) >> 56 == '%')
		return (char_handler(list, flags, wid));
	else if ((*flags << 40) >> 56 == 's' || (*flags << 40) >> 56 == 'S')
		return (string_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'd' || (*flags << 40) >> 56 == 'D' || (*flags << 40) >> 56 == 'i')
		return (decimal_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'u' || (*flags << 40) >> 56 == 'U')
		return (unsigned_decimal_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'f' || (*flags << 40) >> 56 == 'F')
		return (double_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'e' || (*flags << 40) >> 56 == 'E')
		return (expo_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'g' || (*flags << 40) >> 56 == 'G')
		;//return (double_or_expo_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'a' || (*flags << 40) >> 56 == 'A')
		;//return (hexafloat_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'x' || (*flags << 40) >> 56 == 'X')
		return (hexadecimal_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'o' || (*flags << 40) >> 56 == 'O')
		return (octal_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'b' || (*flags << 40) >> 56 == 'B')
		return (binary_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'p')
		return (pointer_handler(list, flags, wid, pre));
	return (0);
}

int				ft_printf(const char *format, ...)
{
	/*va_list		listv;
	size_t 		flags;
	size_t		bytes;
	int			pre;
	int			wid;

	va_start(listv, format);
	bytes = 0;
	pre   = 0;
	wid   = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			flags  = 0;
			flags |= 32;
			bytes += flags_collector(&format, &listv, &flags, &wid, &pre);
			if (*format && format++)
				bytes += everything_handler(&listv, &flags, &wid, &pre);
		}
		else
			bytes += write(1, format++, 1);
	}
	va_end(listv);*/
	return (write(1, "33333", 5));
}
