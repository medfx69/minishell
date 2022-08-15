/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:05:08 by mboukhal          #+#    #+#             */
/*   Updated: 2022/08/15 14:52:21 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/ft_exec.h"

void	free_data(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
		free(data[i]);
	free(data);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_data.ret_val = 1;
		rl_catch_signals = 0;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	return ;
}

void	init_global(char	**e)
{
	int	i;
	int	j;

	g_data.pwd = getenv("PWD");
	g_data.pid = getpid();
	i = -1;
	g_data.env = NULL;
	while (e[++i])
		;
	g_data.env = malloc((i + 1) * sizeof(char *));
	j = -1;
	while (e[++j])
	{
		g_data.env[j] = init_var(1);
		g_data.env[j] = my_recat(g_data.env[j], e[j], ft_strlen(e[j]) + 1);
	}
	g_data.env[j] = NULL;
	g_data.ret_val = 0;
}

char	**cat_cmd(char	**cmd, char c)
{
	int		i;
	char	**str;

	i = 0;
	while (cmd[i] && cmd[i][0] != c)
		i++;
	str = malloc(sizeof(char *) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (cmd[i] && cmd[i][0] != c)
	{
		str[i] = cmd[i];
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	check_ff(char **cmd)
{
	if (**cmd)
	{
		check_for_exit(cmd);
		if ((**cmd == '\"' || **cmd == '\''
				|| **cmd == '|' || **cmd == '-')
			&& cmd[1] == '\0')
		{
			ft_putstr_fd(APP_NAME, STDERR_FILENO);
			ft_putstr_fd(": syntax error near unexpected token `",
				STDERR_FILENO);
			ft_putchar_fd(**cmd, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			g_data.ret_val = 258;
			return (0);
		}
	}
	return (1);
}
