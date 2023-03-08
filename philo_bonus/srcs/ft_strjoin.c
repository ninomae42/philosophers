#include "philo_bonus.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen((char *)src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = ft_strlen((char *)s);
	if (len < maxlen)
		return (len);
	else
		return (maxlen);
}

// size-bounded string concatenation
static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_nlen;
	size_t	src_len;
	size_t	cpy_cnt;

	if (dstsize == 0 && dst == NULL)
		return (ft_strlen((char *)src));
	dst_nlen = ft_strnlen(dst, dstsize);
	src_len = ft_strlen((char *)src);
	if (dstsize <= ft_strlen(dst))
		return (dst_nlen + src_len);
	cpy_cnt = dstsize - ft_strlen(dst) - 1;
	while (*dst != '\0')
		dst++;
	while (*src != '\0' && cpy_cnt > 0)
	{
		*dst = *src;
		dst++;
		src++;
		cpy_cnt--;
	}
	*dst = '\0';
	return (dst_nlen + src_len);
}

static char	*ft_strdup(const char *s1)
{
	char	*p_ret;
	size_t	len_str;

	len_str = ft_strlen((char *)s1) + 1;
	p_ret = (char *)malloc(sizeof(char) * len_str);
	if (p_ret == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(p_ret, s1, len_str);
	return (p_ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_ret;
	size_t	alloc_size;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	alloc_size = sizeof(char)
		* (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	p_ret = (char *)malloc(alloc_size);
	if (p_ret == NULL)
		return (NULL);
	ft_strlcpy(p_ret, s1, alloc_size);
	ft_strlcat(p_ret, s2, alloc_size);
	return (p_ret);
}
