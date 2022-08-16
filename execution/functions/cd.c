/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:47:42 by mait-aad          #+#    #+#             */
/*   Updated: 2022/08/16 15:35:34 by mait-aad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

void	previeus_dir(void)
{
	int	i;

	i = ft_strlen(g_data.pwd);
	while (--i >= 0)
	{
		if (g_data.pwd[i] == '/')
		{
			g_data.pwd[i + 1] = '\0';
			if (access(g_data.pwd, F_OK) == 0)
			{
				chdir(g_data.pwd);
				return ;
			}
		}
	}
}

void	get_dir(char	*dir)
{
	int	i;

	if (access(dir, F_OK) == 0)
	{
		g_data.ret_val = 1;
		printf("minishell: %s: Permission denied\n", dir);
		return ;
	}
	i = chdir(dir);
	if (i == -1)
	{
		printf("cd: no such file or directory: %s\n", dir);
		g_data.ret_val = 1;
		return ;
	}
}

void	ft_cd(char *dir)
{
	int		i;
	char	*out;
	char	*pwds[2];

	pwds[0] = getcwd(NULL, 0);
	i = 0;
	out = NULL;
	if (!dir || (dir[0] == '\0' || (dir[0] == '~' && dir[1] == '\0')))
		out = ft_getenv("HOME");
	else if (dir[0] == '-' && dir[1] == '\0')
		out = ft_getenv("OLDPWD");
	if (out)
	{
		chdir(out);
		free (out);
	}
	else if (dir[0] == '.' && dir[1] == '.' && dir[2] == '\0')
		previeus_dir();
	else
		get_dir(dir);
	pwds[1] = getcwd(NULL, 0);
	mod_env(pwds);
}
