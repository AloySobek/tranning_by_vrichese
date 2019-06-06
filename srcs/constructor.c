/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/06 16:36:19 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	constructor(size_t *flags)
{
	if (*flags & NEG && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = '-';
	if (*flags & HAS && BASE == 8 && !(*flags & ZER) && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = '0';
	if (!(*flags & NEG) && *flags & PLU && (BASE == 10 || *flags & FLO) &&
		!(*flags & NAN) && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = '+';
	if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (BASE == 10
		|| *flags & FLO) && !(*flags & NAN) && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = ' ';
	if ((((*flags & HAS && BASE == 16 && !(*flags & (BIG | ZER))) ||
	*flags & PTR) && EJECT(2)) || (SPEC == 'a' && !(*flags & (INF | NAN))))
	{
		BUFF.g_buff[BUFF.g_count++] = '0';
		BUFF.g_buff[BUFF.g_count++] = 'x';
	}
	else if ((*flags & HAS && BASE == 16 && !(*flags & ZER)
		&& EJECT(2)) || (SPEC == 'A' && !(*flags & (INF | NAN))))
	{
		BUFF.g_buff[BUFF.g_count++] = '0';
		BUFF.g_buff[BUFF.g_count++] = 'X';
	}
	else if (*flags & HAS && BASE == 2 && EJECT(2) &&
		(BUFF.g_buff[BUFF.g_count++] = '0'))
		BUFF.g_buff[BUFF.g_count++] = *flags & BIG ? 'B' : 'b';
}

void	adjustment_wid_pre(size_t *flags, int *wid, int *pre, int len)
{
	!(*flags & FLO) || *flags & INF || *flags & NAN ? *pre -= len : 0;
	*flags & NEG ? (*wid)-- : 0;
	*flags & INF || *flags & NAN ? (*wid) -= 3 : 0;
	(SPEC == 'e' || SPEC == 'E') && !(*flags & (INF | NAN)) ? *wid -= 4 : 0;
	BASE == 8 && *flags & HAS && !(*flags & ZER) ? (*pre)-- : 0;
	*wid -= len > 0 ? len : 0;
	*wid -= *pre > 0 && !(*flags & FLO) ? *pre : 0;
	if (*flags & SPA && !(*flags & PLU) && !(*flags & NEG) && !(*flags & PTR)
		&& !(*flags & NAN) && BASE != 8 && BASE != 16)
		*wid -= 1;
	if (*flags & PLU && !(*flags & (NEG | NAN)) && (BASE == 10 || *flags & FLO))
		*wid -= 1;
	if (SIGN == 32)
	{
		*flags & HAS && BASE == 8 && !(*flags & (ZER | FLO)) ? *wid -= 1 : 0;
		*wid -= (*flags & HAS && (BASE == 16 || BASE == 2) && !(*flags & ZER)
		&& !(*flags & FLO)) ? 2 : 0;
		*wid -= (SPEC == 'a' || SPEC == 'A') && !(*flags & (NAN | INF)) ? 2 : 0;
	}
	else
	{
		if ((*flags & HAS && !(*flags & FLO) && !(*flags & ZER) && BASE != 10)
			|| ((SPEC == 'a' || SPEC == 'A') && !(*flags & (INF | NAN))))
			*wid -= ((BASE == 8) ? 1 : 2);
	}
}

void	fill_width(size_t *flags, int *wid)
{
	if ((*flags & INF || *flags & NAN) && shift(flags, 8, 'r'))
		*flags |= 32;
	if (!(*flags & BIA))
	{
		if (SIGN == 32)
		{
			while ((*wid)-- > 0 && EJECT(1))
				BUFF.g_buff[BUFF.g_count++] = SIGN;
			constructor(flags);
		}
		else
		{
			constructor(flags);
			while ((*wid)-- > 0 && EJECT(1))
				BUFF.g_buff[BUFF.g_count++] = SIGN;
		}
	}
	else
		constructor(flags);
}
