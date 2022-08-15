/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:28:18 by mboukhal          #+#    #+#             */
/*   Updated: 2022/08/15 18:34:50 by mboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

char	*add_sp(char *val, t_lexer *lex, int type)
{
	char	tmp;
	char	tmp2;

	tmp = lex->c;
	tmp2 = lex->contents[lex->i - 1];
	lexer_skip_spaces(lex);
	if (tmp == ' ' && type == T_DQUOT && lex->export
		&& tmp2 != '+' && !(lex->c == '\\' || lex->c == '|'
			|| lex->c == '>' || lex->c == '<') && lex->c)
		val = my_recat(val, " ", ui_strlen(val) + 1);
	return (val);
}

t_token	*lexer_collect_str(t_lexer *lex, int type)
{
	char	*val;

	val = init_var(1);
	if (type == T_OPTION)
	{
		val = ft_realloc(val, 2);
		*val = '-';
		*(val + 1) = '\0';
		lexer_next(lex);
	}
	while (!(lex->c == '\"' || lex->c == '\\' || lex->c == '\''
			|| lex->c == '|' || lex->c == '$' || lex->c == ' '
			|| lex->c == '>' || lex->c == '<')
		&& lex->c)
	{
		val = my_recat(val, &lex->c, ui_strlen(val) + 1);
		lexer_next(lex);
	}
	if (type == T_PROG && (!ft_strncmp(val, "export", 7)
			|| !ft_strncmp(val, "unset", 6)))
		lex->export = 0;
	val = add_sp(val, lex, type);
	return (init_token(type, val));
}

t_token	*lexer_collect_var(t_lexer *lex)
{
	char	*val;

	val = init_var(1);
	lexer_next(lex);
	while ((ft_isalnum(lex->c) || lex->c == '_' || lex->c == '?') && lex->c)
	{
		val = my_recat(val, &lex->c, ui_strlen(val) + 1);
		lexer_next(lex);
	}
	val = ft_getenv_lex(val, lex);
	if (lex->c == ' ' && (lex->contents[lex->i - 1] != '?'))
		val = my_recat(val, " ", ui_strlen(val) + 1);
	if (lex->contents[lex->i - 1] == '?')
		return (init_token(T_STR, val));
	return (init_token(T_DQUOT, val));
}
