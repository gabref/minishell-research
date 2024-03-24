#ifndef TOKEN_H
# define TOKEN_H

typedef struct TOKEN_STRUCT
{
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
	} type;
	char	*value;
}			t_token;

t_token		*init_token(int type, char *value);

#endif
