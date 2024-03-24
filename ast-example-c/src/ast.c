# include "../inc/ast.h"
# include <stdlib.h>

t_ast* init_ast(int type) {
	t_ast* ast = calloc(1, sizeof(t_ast));
	ast->type = type;

	ast->variable_definition_variable_name = NULL;
	ast->variable_definition_value = NULL;

	ast->variable_name = NULL;

	ast->function_call_name = NULL;
	ast->function_call_arguments = NULL;
	ast->function_call_arguments_size = 0;

	ast->string_value = NULL;

	ast->compound_value = NULL;
	ast->compound_size = 0;

	return (ast);
}
