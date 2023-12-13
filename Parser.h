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
class WhileStatement;
class IfStatement;
class ForiStatement;
class ForaStatement;
class DeclarationStatement;
class ExpressionStatement;
class Expression;
class ReturnStatement;
class Statement;
struct ConditionAndBlock;

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

struct ConditionAndBlock {
    Expression * condition;
    CodeBlock * block;
    ConditionAndBlock(Expression * condition, CodeBlock * block) : condition(condition), block(block) {};
};

class WhileStatement : public Statement {
private:
    ConditionAndBlock * conditionAndBlock;
public:
    WhileStatement(ConditionAndBlock * conditionAndBlock) : conditionAndBlock(conditionAndBlock){};
};

class IfStatement : public Statement {
private:
    ConditionAndBlock * ifConditionAndBlock;
    std::vector<ConditionAndBlock*> elsifConditionsAndBlocks;
    ConditionAndBlock * elseConditionAndBlock;
public:
    IfStatement(ConditionAndBlock * ifConditionAndBlock, std::vector<ConditionAndBlock*> elsifConditionsAndBlocks, ConditionAndBlock * elseConditionAndBlock)
        : ifConditionAndBlock(ifConditionAndBlock), elsifConditionsAndBlocks(elsifConditionsAndBlocks), elseConditionAndBlock(elseConditionAndBlock){};
};

class ForStatement : public Statement {
private:
    std::wstring identifier;
    Expression * expression;
    CodeBlock * block;
public:
    ForStatement(const std::wstring & identifier, Expression * expression, CodeBlock * block) :
        identifier(identifier), expression(expression), block(block) {};
};

class DeclarationStatement : public Statement {
private:
    std::wstring identifierName;
    Expression * expression;
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

    FuncDeclaration(const std::wstring &name, const std::vector<Parameter *> &params, CodeBlock * statements, const Position & position) : name(
            name), params(params), statements(statements), position(position) {}

    FuncDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }

private:
    Position position;
    std::wstring name;
    std::vector<Parameter *> params;
    CodeBlock * statements;
};

class FigureDeclaration {
public:

    FigureDeclaration(const std::wstring &name, const std::vector<Parameter> &params, CodeBlock * statements, const Position & position) : name(
            name), params(params), statements(statements), position(position) {}

    FigureDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }

private:
    Position position;
    std::wstring name;
    std::vector<Parameter> params;
    CodeBlock * statements;
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
public:
    Program * parse();
    bool getSemanticError() {return this->semantic_error;};
    bool getSyntaxError() {return this->blocking_syntax_error;};
private:
    bool blocking_syntax_error = false;
    bool semantic_error = false;
    Lexer * lexer;
    ErrorHandler * errorHandler;
    std::optional<Token> token;

    bool consumeIf(unsigned int token_type);
    std::variant<int, double, std::wstring> mustBe(token_type tokenType, Position position, const std::wstring & message);

    FuncDeclaration * parseFuncDecl();
    FigureDeclaration * parseFigureDecl();
    std::vector<Parameter *> parseFunctionParams();
    Parameter * parseParam();
    CodeBlock * parseCodeBlock();
    Statement * parseStatement();
    Statement * parseWhileStatement();
    Statement * parseIfStatement();
    Statement * parseForStatement();
    Statement * parseDeclarationStatement();
    Statement * parseIdentifierOrAssignmentStatement();
    Statement * parseReturnStatement();
    ConditionAndBlock * parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType);
    Expression * parseExpression();
    nullptr_t handleSyntaxError(const Position &position, const std::wstring &message);
    void handleSemanticError(const Position &position, const std::wstring &message);

};


#endif //LEXER_PARSER_H
