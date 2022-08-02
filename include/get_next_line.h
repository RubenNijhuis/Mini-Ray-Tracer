/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 18:11:07 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/08/02 12:13:53 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Old GNL is much better imo */
/* code stolen from my very own pipex */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define GNL_BUFFER_SIZE (256)

# include <sys/types.h> /* ssize_t */

char	*get_next_line(const int fd, ssize_t *status);

char	*gnl_strfjoin(char *s1, char const *s2);
char	*ft_protec_strchr(const char *s, const int c);
char	*ft_strndup_unsafe(const char *s1, const size_t len);

#endif
