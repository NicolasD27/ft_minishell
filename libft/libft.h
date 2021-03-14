/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidescre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:33:46 by nidescre          #+#    #+#             */
/*   Updated: 2021/03/12 16:56:32 by nidescre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **alst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putnbr_fd(int n, int fd);
char			**ft_split(char const *s, char c);
void			ft_putchar_fd(char c, int fd);
char			*ft_itoa(int n);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi(char const *str);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strrchr(char const *s, int c);
char			*ft_strnstr(char const *haystack, char const *needle, int len);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(char const *str);
char			*ft_strcpy(char *dst, char const *src);
int				ft_strlcpy(char *dst, char const *src, int dstsize);
int				ft_strlcat(char *dst, char const *src, int dstsize);
char			*ft_strdup(char const *s1);
char			*ft_strchr(char const *s, int c);
void			*ft_memset(void *b, int c, int len);
void			*ft_memmove(void *dst, const void *src, int len);
void			*ft_memcpy(void *dst, const void *src, int n);
int				ft_memcmp(const void *s1, const void *s2, int n);
void			*ft_memchr(const void *s, int c, int n);
void			*ft_memccpy(void *dst, const void *src, int c, int n);
int				ft_isprint(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
void			*ft_calloc(int count, int size);
void			ft_bzero(void *s, int n);
#endif
