import { exit } from 'process';
import { Statement, Program, Expr, BinaryExpr, NumericLiteral, Identifier, NullLiteral } from './ast';
import { Token, TokenType, tokenize } from './lexer';

export default class Parser {
	private tokens: Token[] = [];

	private not_eof(): boolean {
		return this.tokens[0].type !== TokenType.EOF;
	}

	private at(): Token {
		return this.tokens[0];
	}

	private eat() {
		const prev = this.tokens.shift() as Token;
		return prev;
	}

	private expect(type: TokenType, err: any) {
		const prev = this.tokens.shift() as Token;
		if (!prev || prev.type != type) {
			console.error("Parser Error:\n", err, prev, " - Expecting: ", type);
			exit(1);
		}
		return prev;
	}

	public produceAST(sourceCode: string): Program {
		this.tokens = tokenize(sourceCode);
		const program: Program = {
			kind: "Program",
			body: [],
		};

		while (this.not_eof()) {
			program.body.push(this.parse_statement());
		}
		return program;
	}

	private parse_statement(): Statement {
		// skip to parse expr
		return this.parse_expr();
	}

	private parse_expr(): Expr {
		return this.parse_additive_expr();
	}

	private parse_multiplicative_expr(): Expr {
		let left = this.parse_primary_expr();
		while (this.at().value == '*' || this.at().value == '/' || this.at().value == '%') {
			const operator = this.eat().value;
			const right = this.parse_primary_expr();
			left = {
				kind: "BinaryExpr",
				left,
				right,
				operator,
			} as BinaryExpr;
		}
		return left;
	}

	private parse_additive_expr(): Expr {
		let left = this.parse_multiplicative_expr();
		while (this.at().value == '+' || this.at().value == '-') {
			const operator = this.eat().value;
			const right = this.parse_multiplicative_expr();
			left = {
				kind: "BinaryExpr",
				left,
				right,
				operator,
			} as BinaryExpr;
		}
		return left;
	}

	private parse_primary_expr(): Expr {
		const tk = this.at().type;

		switch (tk) {
			case TokenType.Identifier:
				return { kind: "Identifier", symbol: this.eat().value } as Identifier;
			case TokenType.Null:
				this.eat();
				return { kind: "NullLiteral", value: "null" } as NullLiteral;
			case TokenType.Number:
				return { kind: "NumericLiteral", value: parseFloat(this.eat().value) } as NumericLiteral;
			case TokenType.OpenParen:
				console.log('open paren');
				console.log('eaten: ', this.eat());
				const value = this.parse_expr();
				console.log('got expression: ', value);
				this.expect(TokenType.CloseParen, "Unexpected token found inside parenthesis expre, expected closing parenthesis");
				return value;
			default:
				{
					console.error("Unexpected token", this.at());
					exit(1);
				}
		}
	}
}
