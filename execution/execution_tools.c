/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:41:04 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/16 19:02:06 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t				i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	wcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == c || !(s[i + 1])))
			count++;
		i++;
	}
	return (count);
}

static int	wrlen(char const *s, char c, int t)
{
	int	i;

	i = 0;
	while (s[t] != c && s[t] != 0)
	{
		t++;
		i++;
	}
	return (i);
}

static char	*copy(int t, char const *s, char c)
{
	int		j;
	int		len ;
	char	*str;

	j = 0;
	len = wrlen(s, c, t);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	while (j < len && s[t] != c)
	{
		str[j] = (char)s[t];
		j++;
		t++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		t;
	char	**str;

	i = 0;
	t = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (wcount(s, c) + 1));
	if (!str)
		return (NULL);
	while (i < wcount(s, c))
	{
		while (s[t] == c)
			t++;
		str[i] = copy(t, s, c);
		t += wrlen(s, c, t);
		i++;
	}
	str[i] = 0;
	return (str);
}
