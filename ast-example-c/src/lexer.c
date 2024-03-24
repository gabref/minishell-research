#include "../inc/lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = calloc(1, sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n')
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	int	token_type;

	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\n')
			lexer_skip_whitespace(lexer);
		if (isalnum(lexer->c))
			return (lexer_collect_id(lexer));
		else if (lexer->c == '"')
			return (lexer_collect_string(lexer));
		else if (lexer->c == '=')
			token_type = TOKEN_EQUALS;
		else if (lexer->c == ';')
			token_type = TOKEN_SEMI;
		else if (lexer->c == '(')
			token_type = TOKEN_LPAREN;
		else if (lexer->c == ')')
			token_type = TOKEN_RPAREN;
		else
		{
			printf("Unrecognized character: %c at %d\n", lexer->c, lexer->i);
			exit(1);
		}
		return (lexer_advance_with_token(lexer, init_token(token_type,
					lexer_get_current_char_as_string(lexer))));
	}
	return (void *)0;
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (isalnum(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_ID, value));
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = calloc(1, sizeof(char));
	value[0] = '\0';
	lexer_advance(lexer);
	while (lexer->c != '"')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_STRING, value));
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
