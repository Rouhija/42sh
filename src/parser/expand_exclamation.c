/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:26:30 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/20 11:37:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	head(char *tmp, char *tmp2, t_shell *shell)
{
	int			i;
	int			num;

	i = 1;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	i = HISTORY_SIZE - 1;
	while (!shell->history[i])
		i--;
	i -= num - 1;
	if (i < 0)
		i = 0;
	tmp2 = ft_strjoin(tmp, shell->history[i]);
	return (ft_count_digits_only(num, 10) + 1);
}

static int	tail(char *tmp, char *tmp2, t_shell *shell)
{
	int			i;
	int			num;

	i = 2;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	i = num - 1;
	if (i >= HISTORY_SIZE)
	{
		i = HISTORY_SIZE - 1;
		while (!shell->history[i] && i >= 0)
			i--;
	}
	tmp2 = ft_strjoin(tmp, shell->history[i]);
	return (ft_count_digits_only(num, 10) + 2);
}

static int	word(char *tmp, char *tmp2, t_shell *shell)
{
	int			i;
	char		*str;
	size_t		length;

	i = 1;
	while (ft_isalpha(tmp[i]))
		i++;
	str = ft_strsub(tmp, 1, i);
	i = 0;
	while (i < HISTORY_SIZE && shell->history[i] \
	&& !ft_strstr(shell->history[i], str))
		i++;
	tmp2 = ft_strjoin(tmp, shell->history[i]);
	length = ft_strlen(str);
	free(str);
	return (length + 1);
}

static int	parse(char *tmp, char **tmp2, t_shell *shell)
{
	if (*(tmp + 1) == '!')
	{
		*tmp2 = ft_strjoin(tmp + 2, shell->history[ft_arrlen(shell->history, HISTORY_SIZE) - 1]);
		return (2);
	}
	else if (ft_isdigit(*(tmp + 1)))
		return (head(tmp, *tmp2, shell));
	else if (*(tmp + 1) == '-')
		return (tail(tmp, *tmp2, shell));
	else if (ft_isalpha(*(tmp + 1)))
		return (word(tmp, *tmp2, shell));
	return (0);
}

void			parse_exclamation(char **data, t_shell *shell)
{
	int			i;
	int			j;
	char		*tmp;
	char		*tmp2;
	char		*new;

	i = 0;
	tmp = *data;
	while ((tmp = ft_strchr(tmp, '!')))
	{
		*tmp = '\0';
		i = parse(tmp, &tmp2, shell);
		new = ft_strjoin(tmp2, tmp + i);
		ft_strdel(&tmp2);
		ft_strdel(data);
		*data = new;
		tmp = new;
	}
}
