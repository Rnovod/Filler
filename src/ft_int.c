/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:40:15 by rnovodra          #+#    #+#             */
/*   Updated: 2018/06/28 16:40:15 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/ft_printf.h"

inline	static	void	ft_put_sign_pref(t_data *d, uintmax_t val, int base)
{
	if (d->fl.plus && !d->fl.sign)
		d->buff[d->buff_i++] = '+';
	else if (d->fl.sign && base != 16 && base != 8)
		d->buff[d->buff_i++] = '-';
	else if (d->fl.space && !d->fl.sign && !d->fl.plus)
		d->buff[d->buff_i++] = ' ';
	if ((d->fl.sharp == 1 && (base == 8 || base == 16) &&
		val != 0) || d->chr == 'p')
	{
		d->buff[d->buff_i++] = '0';
		if ((base == 16 && d->chr == 'x') || d->chr == 'p')
			d->buff[d->buff_i++] = 'x';
		else if (base != 8)
			d->buff[d->buff_i++] = 'X';
	}
}

inline	static	void	ft_put_prec(t_data *d, uintmax_t val, int len, int base)
{
	register int		prec;

	prec = d->prec - len;
	if (d->fl.sharp == 1 && base == 8 && val != 0)
		--prec;
	while (prec-- > 0)
	{
		FT_PRINTF_BUFF_SIZE == d->buff_i ? ft_print_buff(d) :
		(d->buff[d->buff_i++] = '0');
	}
}

inline	static	uintmax_t	ft_get_sign_val(t_data *d, va_list *arg)
{
	intmax_t		val;

	if (d->fl.size == 0)
		val = va_arg(*arg, int);
	else if (d->fl.size == 1)
		val = (signed char)va_arg(*arg, int);
	else if (d->fl.size == 2)
		val = (short)va_arg(*arg, int);
	else if (d->fl.size == 3)
		val = (long)va_arg(*arg, intmax_t);
	else if (d->fl.size == 4)
		val = (long long)va_arg(*arg, intmax_t);
	else if (d->fl.size == 5)
		val = (intmax_t)va_arg(*arg, intmax_t);
	else
		val = (ssize_t)va_arg(*arg, intmax_t);
	if (val < 0)
	{
		d->fl.sign = 1;
		return (-val);
	}
	return (val);
}

inline	static	uintmax_t	ft_get_unsign_val(t_data *d, va_list *arg)
{
	d->fl.plus = 0;
	d->fl.space = 0;
	if (d->fl.size == 0)
		return ((unsigned int)va_arg(*arg, unsigned int));
	else if (d->fl.size == 1)
		return ((unsigned char)va_arg(*arg, int));
	else if (d->fl.size == 2)
		return ((unsigned short)va_arg(*arg, int));
	else if (d->fl.size == 3)
		return ((unsigned long)va_arg(*arg, uintmax_t));
	else if (d->fl.size == 4)
		return ((unsigned long long)va_arg(*arg, uintmax_t));
	else if (d->fl.size == 5)
		return ((uintmax_t)va_arg(*arg, uintmax_t));
	else
		return ((size_t)va_arg(*arg, uintmax_t));
}

void						ft_int(t_data *d, va_list *arg, int base)
{
	const	uintmax_t	val = (d->chr == 'D' || d->chr == 'd' || d->chr == 'i') ?
						ft_get_sign_val(d, arg) : ft_get_unsign_val(d, arg);
	const	int			val_len = ft_count_dig(d, val, base);

	if (d->fl.zero && d->prec >= 0)
		d->fl.zero = 0;
	if (d->fl.sign || d->fl.plus || d->fl.space ||
		(d->fl.sharp == 1 && base == 8 && val_len > d->prec))
		d->width--;
	else if ((base == 16 && d->fl.sharp == 1) || d->chr == 'p')
		d->width -= 2;
	if (!d->fl.minus && !d->fl.zero)
		ft_put_width(d, val_len);
	if (d->fl.plus || d->fl.minus || d->fl.space || d->fl.sign ||
		(d->fl.sharp && (base == 8 || base == 16)) || d->chr == 'p')
		ft_put_sign_pref(d, val, base);
	if (d->width > 0 && d->fl.minus == 0 && d->fl.zero)
		ft_put_width(d, val_len);
	if (d->prec > 0 && d->prec > val_len)
		ft_put_prec(d, val, val_len, base);
	if (val_len != 0)
		ft_printf_itoa(d, val, base, val_len);
	if (d->width > 0 && d->fl.minus)
		ft_put_width(d, val_len);
}
