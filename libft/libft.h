/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:55:34 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:20:46 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 32
# define FLAGS "0123456789#+- '.$*hljzL"
# define TYPE_INT "diouxXDOUp"
# define TYPE_PTR "n"
# define TYPE_CHR "cCsS"
# define TYPE_DBL "aAeEfFgG"
# define T_INT 1
# define T_PTR 2
# define T_CHR 3
# define T_DBL 4
# define T_OTHER 5
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdarg.h>
# include <locale.h>
# include <wchar.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_m
{
	char	s;
	int		type;
	int		hh;
	int		h;
	int		ll;
	int		l;
	int		j;
	int		z;
}					t_size;

typedef struct		s_f
{
	int		dol;
	int		hash;
	int		zero;
	int		minus;
	int		sp;
	int		plus;
	int		ap;
	int		width;
	int		prc;
	int		dol_w;
	int		dol_prc;
	int		n;
}					t_flags;

size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				*ft_realloc(void *ptr, size_t ptr_size, size_t size);
void				ft_lstaddb(t_list **alst, t_list *new);
void				ft_lstprint(t_list **alst);
void				ft_memdel_md(void **ptr, size_t size);
int					get_next_line(const int fd, char **line);
char				**ft_bufstr(t_list *head, int fd);
t_list				*ft_lst_create(char *buf, int fd);
int					ft_copy_bn(char **line, char **buf);
int					reading(const int fd, char **line, char **str,
					t_list **head);
int					ft_printf(const char *format, ...);
int					print_format(const char *format, int n, va_list ap,
					va_list cp);
int					parsing(char **str, int n, va_list ap, va_list cp);
int					extract_fmt(char **str, char **fmt, char *specifier);
int					basic_type(char c);
int					arg_num(t_size mod, t_flags flag, va_list ap, va_list cp);
t_size				parse_modifiers(char *fmt, int b_type, char specifier);
t_flags				parse_flags(char *fmt, va_list ap, va_list cp, int n);
int					count_char(char *str, char c);
int					dollar_arg(char *fmt);
int					dollar_width(char *fmt);
int					dollar_precision(char *fmt);
int					dollar_value(char *str);
int					zero_flag(char *fmt);
int					width_value(char *fmt);
int					prc_value(char *fmt);
int					star_value(int dollar, va_list ap, va_list cp);
int					star_value_width(int dollar, int *minus, va_list ap,
					va_list cp);
int					star_value_precision(int dollar, va_list ap, va_list cp);
int					arg_num(t_size mod, t_flags flag, va_list ap, va_list cp);
long long			arg_sg(t_size mod, int	dollar, va_list ap, va_list cp);
long long			conv_sg_dol(t_size mod, int dollar, va_list cp);
long long			conv_sg(t_size mod, va_list ap);
unsigned long long	arg_un(t_size mod, int dollar, va_list ap, va_list cp);
unsigned long long	conv_un(t_size mod, va_list ap);
unsigned long long	conv_un_dol(t_size mod, int dollar, va_list cp);
char				*make_str_num(t_size mod, t_flags flag, long long num);
char				*make_str_unum(t_size mod, t_flags flag,
					unsigned long long num);
char				*itoa_base(unsigned long long num, unsigned long long base);
int					count_digits(unsigned long long num,
					unsigned long long base);
char				make_char(unsigned long long num);
void				apostrophe(char **str, int n);
int					count_sep(unsigned long long num);
char				*str_ap(char *s, char sep, int n);
unsigned long long	u_num(long long num);
void				precision_num(char **str, int prc, unsigned long long num);
void				sign_num(char **str, int sign, t_flags flag);
void				width_num(char **str, t_flags flag, t_size mod);
char				*minus_zero_num(char *str, int len, t_flags flag,
					t_size mod);
void				minus_num(char **str, t_flags flag);
void				sp_num(char **str, t_flags flag);
void				plus_num(char **str, t_flags flag);
void				hash_num(char **str, t_size mod, t_flags flag);
void				make_toupper(char **str);
void				arg_ptr(t_size mod, t_flags flag, va_list ap, va_list cp);
long long			*arg_n(t_size mod, int dollar, va_list ap, va_list cp);
long long			*conv_n_dol(t_size mod, int dollar, va_list cp);
long long			*conv_n(t_size mod, va_list ap);
int					arg_char(t_size mod, t_flags flag, va_list ap, va_list cp);
char				*conv_char(t_size mod, int dollar, va_list ap, va_list cp);
char				*conv_chr_dol(t_size mod, int dollar, va_list cp);
char				*conv_chr(t_size mod, va_list ap);
char				*make_str_wchr(wchar_t *w, t_size mod);
char				*ft_unicode(wchar_t c, char **str);
void				precision_chr(char **str, int prc);
char				*ft_strjoin_leaks(char **s1, char **s2);
int					nonvalid(t_flags flag, t_size mod);
int					star(char *fmt, t_flags *flag, va_list ap, va_list cp);
char				*conv_chr_c(t_size mod, va_list ap);
char				*conv_chr_s(t_size mod, va_list ap);

#endif
