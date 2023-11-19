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
class ReturnStatement;

typedef std::variant<WhileStatement, IfStatement, ForiStatement, ForaStatement, DeclarationStatement, ExpressionStatement, ReturnStatement> statementType;

class CodeBlock;
class Parameter;
class FuncDeclaration;
class Program;

class BoolExpression {

};

class WhileStatement {
private:
    BoolExpression condition;
};

class IfStatement {
private:
    BoolExpression condition;
    CodeBlock * blockTrue;
    CodeBlock * blockFalse;

};

class ForiStatement {
private:
    std::variant<int, std::string> loop_beg;
    std::variant<int, std::string> loop_end;
    std::string identifier;
    CodeBlock * block;
};

class ForaStatement {
private:
    std::string identifier;
    std::string listIdentifer;
    CodeBlock * block;
};

class DeclarationStatement {
private:
    std::string identifireName;
    BoolExpression expression;
};

class ExpressionStatement {
private:
    std::string identifireName;
    BoolExpression expression;
};

class ReturnStatement {
private:
    BoolExpression expression;
};

class CodeBlock {
public:
    CodeBlock(const std::vector<statementType> &statement) : statement(statement) {}

    CodeBlock() {}

private:
    std::vector<statementType> statement;
};

class Parameter {
public:
    Parameter(const std::string &name) : name(name) {}

    const std::string &getName() const {
        return name;
    }
private:
    std::string name;
};

class FuncDeclaration {
public:

    FuncDeclaration(const std::string &name, const std::vector<Parameter> &params, const CodeBlock &statements) : name(
            name), params(params), statements(statements) {}

    FuncDeclaration() {}

    const std::string &getName() const {
        return name;
    }

private:
    std::string name;
    std::vector<Parameter> params;
    CodeBlock statements;
};

class Program {
public:
    Program(const std::unordered_map<std::string, FuncDeclaration> &functions) : functions(functions) {}

    Program() {}

private:
    std::unordered_map<std::string, FuncDeclaration> functions;
};

class Parser {
    Lexer * lexer;
    std::optional<Token> token;
    Program parse();
    bool consumeIf(unsigned int token_type);

    std::optional<FuncDeclaration> parseFuncDecl();
    std::vector<Parameter> parseParams();
    std::optional<Parameter> parseParam();
    CodeBlock parseCodeBlock();
    std::optional<statementType> parseStatement();
    std::optional<WhileStatement> parseWhileStatement();
    std::optional<IfStatement> parseIfStatement();
    std::optional<ForiStatement> parseForiStatement();
    std::optional<ForaStatement> parseForaStatement();
    std::optional<DeclarationStatement> parseDeclarationStatement();
    std::optional<ExpressionStatement> parseExpressionStatement();
    std::optional<ReturnStatement> parseReturnStatement();

};


#endif //LEXER_PARSER_H
