/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:55:43 by paranha           #+#    #+#             */
/*   Updated: 2024/07/01 18:58:14 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinsep(char *s1, char *s2, unsigned int sep)
{
	char	*new;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	new = (char *)malloc((size1 + size2 + 2) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, size1 + 1);
	new[size1] = sep;
	ft_strlcpy(new + size1 + 1, s2, size2 + 1);
	return (new);
}

void	ft_sort_vars(char **argv, int minor)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		minor = i;
		j = i;
		while (argv[j])
		{
			if (ft_strncmp(argv[j], argv[minor], ft_strchr(argv[j], '=')
					- argv[j]) < 0)
				minor = j;
			j++;
		}
		if (i != minor)
		{
			tmp = argv[i];
			argv[i] = argv[minor];
			argv[minor] = tmp;
		}
		i++;
	}
}

int	ft_is_valid_name(char *name)
{
	int	i;

	if (!isalpha(name[0]) && name[0] != '_')
	{
		ft_status(1);
		ft_putendl_fd("export: not a valid identifier", 2);
		return (0);
	}
	i = 1;
	while (name[i] != '\0')
	{
		if (!isalnum(name[i]) && name[i] != '_')
		{
			ft_status(1);
			ft_putendl_fd("export: not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
