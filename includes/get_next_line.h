/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:34:05 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/19 15:14:50 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFFER_SIZE  42

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char const *s2, size_t symbol_n);
int		ft_strchr_gnl(const char *s, int c);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen_gnl(const char *s);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);

#endif
