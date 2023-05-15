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
        lexer->nextToken();
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
        lexer->nextToken();
        return Parameter(std::get<std::string>(token->getValue()));
    }
    return std::nullopt;
}

CodeBlock Parser::parseCodeBlock() {
    std::vector<statementType> statements;

    return CodeBlock(statements);
}
