/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 05:25:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/04/09 05:49:22 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rainbow.h"

void	set_3_digit(char *start, unsigned char nb)
{
	start[0] = nb / 100 % 10 + '0';
	start[1] = nb / 10 % 10 + '0';
	start[2] = nb % 10 + '0';
}

void	change_rgb(int fd_urand, unsigned char rgb[3])
{
	char	changes[3];

	if (!rgb[0] && !rgb[1] && !rgb[2])
	{
		read(fd_urand, rgb, 3);
		for (int i = 0; i < 3; ++i)
		{
			if (rgb[i] <= MIN_RGB)
				rgb[i] = MIN_RGB;
			else if (rgb[i] >= MAX_RGB)
				rgb[i] = MAX_RGB;
		}
		return ;
	}
	read(fd_urand, changes, 3);
	for (int i = 0; i < 3; ++i)
	{
		if (changes[i] < 0 && rgb[i] + changes[i] % MOD_CHANGES < MIN_RGB)
			rgb[i] = MIN_RGB;
		if (changes[i] > 0 && rgb[i] > MAX_RGB - changes[i] % MOD_CHANGES)
			rgb[i] = MAX_RGB;
		else
			rgb[i] += changes[i] % MOD_CHANGES;
	}
}

void	set_esc_code(int fd_urand)
{
	static	unsigned char	rgb[3] = {0};
	char	esc_code[] = "[38;2;012;012;012m";

	change_rgb(fd_urand, rgb);
	set_3_digit(esc_code + 7, rgb[0]);
	set_3_digit(esc_code + 11, rgb[1]);
	set_3_digit(esc_code + 15, rgb[2]);
	write(1, esc_code, 19);
}

int	is_colorable(char c)
{
	return (c < 0 || (c > ' ' && c <= '~'));
}

int	rainbow(void)
{
	int	br;
	int fd_urand;
	char buf[BIG_NUM];
	
	fd_urand = open("/dev/random", O_RDONLY);
	if (fd_urand < 0)
		exit(1);
	do
	{
		br = read(0, buf, BIG_NUM);
		for (int i = 0; i < br; ++i)
		{
			if (is_colorable(buf[i]))
				set_esc_code(fd_urand);
			write(1, buf + i, 1);
		}
	} while (br > 0);
	write(1, "[0m", 4);
	return (0);
}