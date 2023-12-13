//
// Created by mpkow on 15.05.2023.
//

#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include "lexer.h"

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H
class BoolExpression;
class WhileStatement;
class IfStatement;
class ForiStatement;
class ForaStatement;
class DeclarationStatement;
class ExpressionStatement;
class Expression;
class ReturnStatement;
class Statement;

typedef std::variant<WhileStatement, IfStatement, ForiStatement, ForaStatement, DeclarationStatement, ExpressionStatement, ReturnStatement> statementType;

class CodeBlock;
class Parameter;
class FigureDeclaration;
class FuncDeclaration;
class Program;

class Statement {
public:
    Statement(){}
};

class Expression {
public:
    Expression(){}
    Expression(Expression * left_expression, Expression * right_expression, const Position & position) : left_expression(left_expression), right_expression(right_expression),
                                                                                          position(position) {}
private:
    Expression * left_expression;
    Expression * right_expression;
    Position position;
};

class BoolExpression {

};

class WhileStatement : public Statement {
private:
    BoolExpression condition;
};

class IfStatement : public Statement {
private:
    BoolExpression condition;
    CodeBlock * blockTrue;
    CodeBlock * blockFalse;

};

class ForStatement : public Statement {
private:
    bool isRange;
    Expression * range_beg;
    Expression * range_end;
    std::wstring identifier;
    CodeBlock * block;
};

class DeclarationStatement : public Statement {
private:
    std::wstring identifireName;
    BoolExpression expression;
};

class ReturnStatement : public Statement {
private:
    Expression * expression;
};


class CodeBlock {
public:
    CodeBlock(const std::vector<Statement*> &statements) : statements(statements) {}

    CodeBlock() {}

private:
    std::vector<Statement*> statements;
};

class Parameter {
public:
    Parameter(const std::wstring &name) : name(name) {}

    const std::wstring &getName() const {
        return name;
    }
private:
    std::wstring name;
};

class FuncDeclaration {
public:

    FuncDeclaration(const std::wstring &name, const std::vector<Parameter> &params, const CodeBlock &statements, const Position & position) : name(
            name), params(params), statements(statements), position(position) {}

    FuncDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }

private:
    Position position;
    std::wstring name;
    std::vector<Parameter> params;
    CodeBlock statements;
};

class FigureDeclaration {
public:

    FigureDeclaration(const std::wstring &name, const std::vector<Parameter> &params, const CodeBlock &statements, const Position & position) : name(
            name), params(params), statements(statements), position(position) {}

    FigureDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }

private:
    Position position;
    std::wstring name;
    std::vector<Parameter> params;
    CodeBlock statements;
};

class Program {
public:
    Program(const std::unordered_map<std::wstring, FuncDeclaration> &functions, const std::unordered_map<std::wstring, FigureDeclaration> &figures) : functions(functions), figures(figures) {}

    Program() {}

private:
    std::unordered_map<std::wstring, FuncDeclaration> functions;
    std::unordered_map<std::wstring, FigureDeclaration> figures;
};

class Parser {
    Lexer * lexer;
    std::optional<Token> token;
    Program parse();
    bool consumeIf(unsigned int token_type);

    std::optional<FuncDeclaration> parseFuncDecl();
    std::optional<FigureDeclaration> parseFigureDecl();
    std::vector<Parameter> parseParams();
    std::optional<Parameter> parseParam();
    std::optional<CodeBlock> parseCodeBlock();
    Statement * parseStatement();
    Statement * parseWhileStatement();
    Statement * parseIfStatement();
    Statement * parseForStatement();
    Statement * parseDeclarationStatement();
    Statement * parseReturnStatement();

};


#endif //LEXER_PARSER_H
