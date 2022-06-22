/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:53 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/08 13:20:58 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* WARNING: THIS PRINTF ASSUMES THAT WRITE TO FD ALWAYS SUCCEEDS 
 * if it doesn't, it won't segfault, but the return value might not
 * be accurate. */
/* format: %[flags][minimum field width][period[precision]]<arg type> */
int	ft_printf(const char *format, ...);
int	ft_dprintf(const int fd, const char *format, ...);

#endif
