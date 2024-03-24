import { readFile } from 'fs/promises';
import Parser from './parser';
import { inspect } from 'util';
import { evaluate } from './interpreter';

async function repl() {
	const parser = new Parser();
	console.log("Parser v0.1.0");
	const source = await readFile('test.txt', 'utf8');
	const program = parser.produceAST(source);
	console.log(inspect(program, false, null, true));

	const result = evaluate(program);
	console.log(inspect(result, false, null, true));
}

repl();
