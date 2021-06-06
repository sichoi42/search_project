#include "search_engine.h"

void	int_to_string(int i, char *s)
{
	int j;

	j = 5;
	while (i != 0)
	{
		s[10 - j] = i % 10 + '0';
		i /= 10;
		j++;
	}
}

int string_to_int(char *s1)
{
	int i,n;
	char *s2="doc000.txt";

	i = 0;
	n=0;
	while (s1[i])
	{
		if (s1[i] - s2[i] != 0)
		{
			n *= 10;
			n += s1[i] - s2[i];
		}
		i++;
	}
	return n;
}

int		is_prime(int nb)
{
	int i;

	if (nb <= 1)
		return (0);
		i = 2;
	while (i <= sqrt(nb))
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int		find_next_prime(int nb)
{
	while (1)
	{
		if (is_prime(nb) == 1)
			break;
		nb++;
	}
	return nb;
}

int transform(char *key)
{
	int i;

	i = 0;
	while (*key)
	{
		i += *key;
		key++;
	}
	return i;
}

int hash(char *key)
{
	int i = transform(key);
	return (i % table_size);
}

size_t		ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

size_t		ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	int i;

	if (src == 0)
		return (0);
	if (dstsize != 0)
	{
		i = 0;
		while (src[i] && dstsize != 1)
		{
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}

size_t		is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}

size_t		find_first(char *s1)
{
	size_t	i;

	i = 0;
	while (i < strlen(s1))
	{
		if (is_alpha(s1[i]) == 1)
			break;
		i++;
	}
	return (i);
}

size_t		find_last(char *s1)
{
	size_t	i;

	i = 0;
	while (i < strlen(s1))
	{
		if (is_alpha(s1[strlen(s1) - i - 1]) == 1)
			break;
		i++;
	}
	return (strlen(s1) - i);
}

char		*ft_strtrim(char *s1)
{
	size_t	first;
	size_t	last;
	char	*trim;

	first = find_first(s1);
	last = find_last(s1);
	if (first >= last)
		return (strdup(""));
	if ((trim = malloc(sizeof(char) * (last - first + 1))) == NULL)
		return (NULL);
	ft_strlcpy(trim, s1 + first, last - first + 1);
	return (trim);
}
