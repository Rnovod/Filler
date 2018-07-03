/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:01:31 by rnovodra          #+#    #+#             */
/*   Updated: 2018/06/28 16:01:31 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/ft_printf.h"

void		ft_conv(t_data *d, char chr, va_list *arg)
{
	va_list		*get_arg;

	if (d->width < 0)
	{
		d->width = -d->width;
		d->fl.minus = 1;
	}
	get_arg = d->data_arg != 0 ? ft_count_arg(d, d->data_arg) : arg;
	d->chr = chr;
	if (chr == 'D' || chr == 'U' ||
		chr == 'O' || chr == 'p' || chr == 'C')
		d->fl.size = 3;
	if (chr == 'd' || chr == 'i' || chr == 'D' ||
		chr == 'U' || chr == 'u')
		ft_int(d, get_arg, 10);
	else if (chr == 'o' || chr == 'O')
		ft_int(d, get_arg, 8);
	else if (chr == 'x' || chr == 'X' || chr == 'p')
		ft_int(d, get_arg, 16);
	else if (chr == 'b')
		ft_int(d, get_arg, 2);
	else if (chr == 'c' || chr == 'C')
		ft_char(d, va_arg(*get_arg, int));
	else if (chr == 's' && d->fl.size != 3)
		ft_string(d, va_arg(*get_arg, char*));
	else if (chr == 'S' || chr == 's')
		ft_wstring(d, va_arg(*get_arg, wchar_t*));
	else
		ft_char(d, chr);
}