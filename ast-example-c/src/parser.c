#include "../inc/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = calloc(1, sizeof(t_parser));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->previous_token = parser->current_token;
	return (parser);
}

void	parser_eat(t_parser *parser, int token_type)
{
	if (parser->current_token->type == token_type)
	{
		parser->previous_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
}
	else
	{
		printf("Unexpected token: %s with type %d at %d\n",
			parser->current_token->value, parser->current_token->type,
			parser->lexer->i);
		exit(1);
	}
}

t_ast	*parser_parse(t_parser *parser)
{
	return (parser_parse_statements(parser));
}

t_ast	*parser_parse_statement(t_parser *parser)
{
	if (parser->current_token->type == TOKEN_ID)
	{
		return (parser_parse_variable(parser));
	}
	else if (parser->current_token->type == TOKEN_STRING)
	{
		return (parser_parse_string(parser));
	}
	else if (parser->current_token->type == TOKEN_LPAREN)
	{
		return (parser_parse_compound(parser));
	}
	else
	{
		printf("Unexpected token: %s with type %d at %d\n",
			parser->current_token->value, parser->current_token->type,
			parser->lexer->i);
		exit(1);
	}
}

t_ast	*parser_parse_statements(t_parser *parser)
{
	t_ast	*compound;
	t_ast	*ast_statement;

	compound = init_ast(AST_COMPOUND);
	compound->compound_value = calloc(1, sizeof(t_ast *));
	ast_statement = parser_parse_statement(parser);
	compound->compound_value[0] = ast_statement;
	while (parser->current_token->type == TOKEN_SEMI)
	{
		parser_eat(parser, TOKEN_SEMI);
		ast_statement = parser_parse_statement(parser);
		compound->compound_size++;
		compound->compound_value = realloc(compound->compound_value,
				(compound->compound_size + 1) * sizeof(t_ast *));
		compound->compound_value[compound->compound_size++] = ast_statement;
	}
	return (compound);
}

t_ast		*parser_parse_expr(t_parser *parser);

t_ast		*parser_parse_factor(t_parser *parser);

t_ast		*parser_parse_term(t_parser *parser);

t_ast		*parser_parse_function_call(t_parser *parser);

t_ast		*parser_parse_variable(t_parser *parser);

t_ast	*parser_parse_variable_definition(t_parser *parser)
{
	char	*variable_name;
	t_ast	*variable_value;
	t_ast	*variable_definition;

	parser_eat(parser, TOKEN_ID);
	variable_name = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);
	parser_eat(parser, TOKEN_EQUALS);
	variable_value = parser_parse_expr(parser);
	variable_definition = init_ast(AST_VARIABLE_DEFINITION);
	variable_definition->variable_definition_variable_name = variable_name;
	variable_definition->variable_definition_value = variable_value;
	return variable_definition;
}

t_ast		*parser_parse_string(t_parser *parser);

t_ast		*parser_parse_compound(t_parser *parser);

t_ast	*parser_parse_id(t_parser *parser)
{
	if (strcmp(parser->current_token->value, "var") == 0)
		return (parser_parse_variable_definition(parser));
	else
		return (parser_parse_variable(parser));
}
