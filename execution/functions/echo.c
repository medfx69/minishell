/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:42:48 by mait-aad          #+#    #+#             */
/*   Updated: 2022/08/14 15:36:29 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

// TODO: check for argumant
// bash: -r hi
// mini: -rhi
char	*ft_echo(char	**inputs, int newlin)
{
	int		i;
	char	*out;

	i = -1;
	out = NULL;
	while (inputs[++i])
	{
		if (inputs[i + 1])
			printf("%s ", inputs[i]);
		else
			printf("%s", inputs[i]);
	}
	if (newlin == 0)
		return (0);
	printf("\n");
	return (NULL);
}
