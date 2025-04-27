/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:48:39 by geudes            #+#    #+#             */
/*   Updated: 2025/04/09 05:48:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAINBOW_H
# define RAINBOW_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

# define P_C_SIZE 512
# define CAT_N_SIZE 4
# define BIG_NUM 16384

# define MAX_RGB 255
# define MIN_RGB 128
# define MOD_CHANGES 8

# if MIN_RGB < 0 || MIN_RGB > 255
#  error "Error: MIN_RGB Value\n"
# endif
# if MAX_RGB < 0 || MAX_RGB > 255
#  error "Error: MAX_RGB Value\n"
# endif
# if MIN_RGB > MAX_RGB
#  error "Error: MIN_RGB > MAX_RGB\n"
# endif
# if MOD_CHANGES > MAX_RGB - MIN_RGB + 1
#  error "Error: MOD_CHANGES > (MAX_RGB - MIN_RGB  + 1)\n"
# endif
# if MOD_CHANGES <  1
#  error "Error: MOD_CHANGES < 1\n"
# endif

int		rainbow(void);

#endif