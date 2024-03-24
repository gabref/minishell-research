#include "../inc/lexer.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_token	*token;

	t_lexer *lexer = init_lexer("var name = \"John Doe\";\n"
								"print(name);\n");
	token = (void *)0;
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		printf("TOKEN(%d, %s)\n", token->type, token->value);
	}
	return (0);
}
