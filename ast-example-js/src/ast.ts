export type NodeType = "Program" | "NumericLiteral" | "Identifier" | "BinaryExpr" | "NullLiteral";

export interface Statement {
	kind: NodeType;
}

export interface Program extends Statement {
	kind: "Program";
	body: Statement[];
}

export interface Expr extends Statement {
}

export interface BinaryExpr extends Expr {
	kind: "BinaryExpr";
	left: Expr;
	right: Expr;
	operator: string;
}

export interface Identifier extends Expr {
	kind: "Identifier";
	symbol: string;
}

export interface NumericLiteral extends Expr {
	kind: "NumericLiteral";
	value: number;
}

export interface NullLiteral extends Expr {
	kind: "NullLiteral";
	value: "null";
}
