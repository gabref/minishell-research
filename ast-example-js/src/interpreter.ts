import { RuntimeVal, NumberVal, NullVal } from "./values"
import { Statement, NumericLiteral, BinaryExpr, Program } from "./ast"
import { exit } from "process";

function eval_program(program: Program): RuntimeVal {
	let lastEvaluated: RuntimeVal = { value: "null", type: "null" } as NullVal;
	for (const statement of program.body) {
		lastEvaluated = evaluate(statement);
	}
	return lastEvaluated;
}

function eval_numeric_expr(lhs: NumberVal, rhs: NumberVal, operator: string): NumberVal {
	let result: number;
	if (operator == "+")
		result = lhs.value + rhs.value;
	else if (operator == "-")
		result = lhs.value - rhs.value;
	else if (operator == "*")
		result = lhs.value * rhs.value;
	else if (operator == "/")
		// TODO: division by zero
		result = lhs.value / rhs.value;
	else if (operator == "%")
		result = lhs.value % rhs.value;
	else {
		console.error("unknown operator", operator);
		exit(1);
	}
	return { value: result, type: 'number' };
}

function eval_binary_expression(binop: BinaryExpr): RuntimeVal {
	const lhs = evaluate(binop.left);
	const rhs = evaluate(binop.right);

	if (lhs.type == 'number' && rhs.type == 'number') {
		return eval_numeric_expr(lhs as NumberVal, rhs as NumberVal, binop.operator);
	}
	return { value: "null", type: "null" } as NullVal;
}

export function evaluate(astNode: Statement): RuntimeVal {
	switch (astNode.kind) {
		case "NumericLiteral":
			return {
				value: ((astNode as NumericLiteral).value),
				type: "number",
			} as NumberVal;
		case "NullLiteral":
			return { value: "null", type: "null" } as NullVal;
		case "BinaryExpr":
			return eval_binary_expression(astNode as BinaryExpr);
		case "Program":
			return eval_program(astNode as Program);
		default:
			console.error("this ast node has not yet been setup for intereptation", astNode);
			exit(1);
	}
}
