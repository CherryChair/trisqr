//
// Created by mpkow on 15.05.2023.
//

#include "Parser.h"

Program Parser::parse() {
    std::unordered_map<std::string, FuncDeclaration> * functions = {};
    token = lexer->nextToken();
    std::optional<FuncDeclaration> funcDecl;
    while(funcDecl = parseFuncDecl()){
        std::string fName = funcDecl->getName();
        if(functions->find(fName) != functions->end()){
            (*functions)[fName] = *funcDecl;
        } else {
//            error
        }
    }
    return Program(*functions);
}

bool Parser::consumeIf(unsigned int token_type) {
    if(token->getTokenType() == token_type) {
        token = lexer->nextToken();
        return true;
    }
    return false;
}

std::optional<FuncDeclaration> Parser::parseFuncDecl() {
    if (!consumeIf(FUNC_TYPE)){
        return std::nullopt;
    }
    token = lexer->nextToken();
    if(token->getTokenType() != IDENTIFIER_TYPE){
        //error
    }
    std::string name = std::get<std::string>(token->getValue());
    token = lexer->nextToken();
    if (!consumeIf(L_BRACKET_TYPE)){
        //error missing l_bracket
    }
    std::vector<Parameter> params = parseParams();
    if (!consumeIf(R_BRACKET_TYPE)){
        //error missing r_bracket
    }
    if (!consumeIf(L_CURL_BRACKET_TYPE)){
        //error missing l_curl_bracket
    }
    CodeBlock block = parseCodeBlock();
    if (!consumeIf(R_CURL_BRACKET_TYPE)){
        //error missing r_curl_bracket
    }
    return FuncDeclaration(name, params, block);
}

std::vector<Parameter> Parser::parseParams() {
    std::vector<Parameter> params;
    std::unordered_map<std::string, bool> paramsMap;
    std::optional<Parameter> param = parseParam();
    if (param) {
        params.push_back(*param);
        paramsMap[param->getName()] = true;
        while (consumeIf(COMMA_TYPE)){
            param = parseParam();
            if(!param){
                //error missing param
            } else if (paramsMap.find(param->getName()) != paramsMap.end()) {
                //error duplicate param
            } else {
                params.push_back(*param);
                paramsMap[param->getName()] = true;
            }
        }
    }

    return params;
}

std::optional<Parameter> Parser::parseParam() {
    if(token->getTokenType() == IDENTIFIER_TYPE){
        token = lexer->nextToken();
        return Parameter(std::get<std::string>(token->getValue()));
    }
    return std::nullopt;
}

CodeBlock Parser::parseCodeBlock() {
    std::vector<statementType> statements;
    std::optional<statementType> statement;
    while (statement = parseStatement()){
        statements.push_back(*statement);
    }

    return CodeBlock(statements);
}

std::optional<statementType> Parser::parseStatement() {
    std::optional<statementType> statement;
    if((statement = parseWhileStatement()) ||
        (statement = parseIfStatement()) ||
        (statement = parseForiStatement()) ||
        (statement = parseForaStatement()) ||
        (statement = parseDeclarationStatement()) ||
        (statement = parseExpressionStatement()) ||
        (statement = parseReturnStatement()))
        return statement;
    return std::nullopt;

}

std::optional<WhileStatement> Parser::parseWhileStatement() {
    if(!consumeIf(IF_TYPE)){
        return std::nullopt;
    }
    if(!consumeIf(L_BRACKET_TYPE)){
        //error missing bracket
    }


    return std::optional<WhileStatement>();
}

std::optional<IfStatement> Parser::parseIfStatement() {
    return std::optional<IfStatement>();
}

std::optional<ForiStatement> Parser::parseForiStatement() {
    return std::optional<ForiStatement>();
}

std::optional<ForaStatement> Parser::parseForaStatement() {
    return std::optional<ForaStatement>();
}

std::optional<DeclarationStatement> Parser::parseDeclarationStatement() {
    return std::optional<DeclarationStatement>();
}

std::optional<ExpressionStatement> Parser::parseExpressionStatement() {
    return std::optional<ExpressionStatement>();
}

std::optional<ReturnStatement> Parser::parseReturnStatement() {
    return std::optional<ReturnStatement>();
}
