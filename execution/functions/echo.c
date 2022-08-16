/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:42:48 by mait-aad          #+#    #+#             */
/*   Updated: 2022/08/16 15:28:00 by mait-aad         ###   ########.fr       */
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
	g_data.ret_val = 0;
	if (newlin == 0)
		return (0);
	printf("\n");
	return (NULL);
}
