# include "../inc/token.h"
# include <stdlib.h>

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}
