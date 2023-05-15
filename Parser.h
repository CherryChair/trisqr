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

class Expression {

};

class WhileStatement {
};

class IfStatement {

};

class ForiStatement {

};

class ForaStatement {

};

class DeclarationStatement {

};

class ExpressionStatement {

};

class ReturnStatement {

};

typedef std::variant<WhileStatement, IfStatement, ForiStatement, ForaStatement, DeclarationStatement, ExpressionStatement, ReturnStatement> statementType;

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

};


#endif //LEXER_PARSER_H
