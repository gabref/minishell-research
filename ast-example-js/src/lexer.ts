export enum TokenType {
	Null,
	Number,
	Identifier,
	Equals,
	OpenParen, CloseParen,
	BinaryOpearator,
	Let,
	EOF,
}

const KEYWORDS: Record<string, TokenType> = {
	let: TokenType.Let,
	null: TokenType.Null,
};

export interface Token {
	value: string;
	type: TokenType;
}

function createToken(value = '', type: TokenType): Token {
	return { value, type };
}

function isalpha(c: string): boolean {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

function isdigit(c: string): boolean {
	return c >= '0' && c <= '9';
}

function isspace (str: string) {
	return (str === ' ' || str === '\t' || str === '\n');
}

export function tokenize(sourceCode: string): Token[] {
	const tokens = new Array<Token>();
	const src = sourceCode.split('');

	while (src.length > 0) {
		if (src[0] == '(')
			tokens.push(createToken(src.shift(), TokenType.OpenParen));
		else if (src[0] == ')')
			tokens.push(createToken(src.shift(), TokenType.CloseParen));
		else if (src[0] == '*' || src[0] == '+' || src[0] == '-' || src[0] == '/' || src[0] == '%')
			tokens.push(createToken(src.shift(), TokenType.BinaryOpearator));
		else if (src[0] == '=')
			tokens.push(createToken(src.shift(), TokenType.Equals));
		else {
			// handle multicharacter tokens
			if (isdigit(src[0])) {
				let num = '';
				while (src.length > 0 && isdigit(src[0])) {
					num += src.shift();
				}
				tokens.push(createToken(num, TokenType.Number));
			} else if (isalpha(src[0])) {
				let ident = '';
				while (src.length > 0 && isalpha(src[0])) {
					ident += src.shift();
				}
				// check for reserved keywords
				const reserved = KEYWORDS[ident];
				if (typeof reserved == 'number')
					tokens.push(createToken(ident, reserved));
				else
					tokens.push(createToken(ident, TokenType.Identifier));
			} else if (isspace(src[0])) {
				src.shift();
			} else {
				console.log('Pos: ', src[0], '<\n', src);
				throw new Error(`Unexpected character: ${src[0]}`);
			}
		}
	}

	tokens.push(createToken('', TokenType.EOF));
	return tokens;
}

// import { readFile } from 'fs/promises';
//
// async function main() {
// 	const source = (await readFile('test.txt')).toString();
// 	for (const token of tokenize(source))
// 		console.log(token)
// }
//
// main().catch(console.error);
