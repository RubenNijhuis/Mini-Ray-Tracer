/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_util.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:59:18 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/06/22 14:57:11 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_UTIL_H
# define PF_UTIL_H

# include <stddef.h>

/* format: %[flags][minimum field width][period[precision]]<arg type> */

# define FT_PRINTF_VALID_FLAGS ("# +-0")
/*
#: create a 0x for x(hexadecimal) or 0X for X.
(space): Leave a space in front of a signed conversion when positive.
+: Add a plus for when a signed conv is positive. overrides space.
-: for field width, add after the argument, not before. if 0 present,
   will be converted to space.
0: field width filled with zeroes.
 */

/* NOTE: % IS MISSING HERE! INTENTIONAL! */
# define FT_PRINTF_VALID_ARGS ("cspdiuxX")
/* # define FT_PRINTF_SIGNED_CONVERSION_ARGS ("di") */

# define FT_PRINTF_NULL_MESSAGE ("(null)")

/*
typedef struct s_printf_args
{
	char	hash_flag; - 1 if the # is present in the flags.
	char	sign_flag; - the sign flag: either + or ` '.
	char	argument_type; - the argument type, such as d.
	char	should_uppercase; - 1 if the entire argument should be uppercase.
	char	min_field_width_right; - 1 if the minimum field width should be 
								     on the right of the argument.
	char	fw_char; - the field width char, either 0 or ` '.
	char	should_not_be_freed; 1 if it the string should not be freed.
				Default 0. This is when you wouldn't want to alloc something,
				such as for a string or char. Note that should_uppercase
				wouldn't work anymore, but that's OK since that's not in the
				real printf anyways.
	int		min_field_width; - the miminum field width.
	int		precision; - precision. -1 if not present.
	int		fd; - the file descriptor to write to.
}				t_printf_args; */
typedef struct s_printf_args
{
	char	hash_flag;
	char	sign_flag;
	char	argument_type;
	char	should_uppercase;
	char	min_field_width_right;
	char	fw_char;
	char	should_not_be_freed;
	int		min_field_width;
	int		precision;
	int		fd;
}				t_printf_args;

/*
typedef struct	s_printf_lengths
{
	int	arg_actual_len;  -   actual length of the argument.
	int	arg_perceived_len; - the length of the "percieved" argument,
							 including the zeroes from the precision.
							 Should equal precision.
	int	special_front_len; - the length of the additional stuff
							 in front(0x, +, -, space).
}				t_printf_lengths; */
typedef struct s_printf_lengths
{
	int	arg_actual_len;
	int	arg_perceived_len;
	int	special_front_len;
}				t_printf_lengths;

int		should_prepend_0x(t_printf_args *pfargs, const void *val);
int		parse_args(const char *s, t_printf_args *pfargs);
void	write_special_front(t_printf_args *pfargs, const void *val,
			int *bytes_written);
void	write_minfield(t_printf_args *pfargs, t_printf_lengths *plens,
			int *bytes_written);
void	write_main_arg(const char *str, t_printf_args *pfargs,
			t_printf_lengths *plens, int *bytes_written);

int		print_arg(t_printf_args *pfargs, const void *val, char *str, int len);

int		print_s(t_printf_args *pfargs, const char *s);
int		print_c(t_printf_args *pfargs, const char c);
int		print_di(t_printf_args *pfargs, const int i);
int		print_u(t_printf_args *pfargs, const unsigned int u);
int		print_p(t_printf_args *pfargs, const void *p);
int		print_x(t_printf_args *pfargs, const unsigned int i);

int		ft_cisupper(const int c);
char	*ft_uitoa(unsigned int n);
char	*ft_itoa_hex_size_t(size_t nbr);

#endif